#!/bin/bash

UNISTD_32="/usr/include/asm/unistd_32.h"
UNISTD_64="/usr/include/asm/unistd_64.h"

OUTPUT_32="./syscall_table32.h"
OUTPUT_64="./syscall_table64.h"

HANDLER_32="&syscall32_generic_handler"
HANDLER_64="&syscall64_generic_handler"

PATTERN_SYS_NB="#define __NR_"
PATTERN_PROTOTYPE_SECTION_BEG="SYNOPSIS"
PATTERN_PROTOTYPE_SECTION_END="DESCRIPTION"

PATTERN_UNIMPLEMENTED="UNIMPLEMENTED"
PATTERN_UNIMPLEMENTED_LENGTH=`expr length "$PATTERN_UNIMPLEMENTED"`

PATH_GET_REAL_TYPE="./get_real_type"

gcc "$PATH_GET_REAL_TYPE".c -o "$PATH_GET_REAL_TYPE"
COMPILED_GET_REAL_TYPE=$?


UNKNOWN_ARG=" // Unknown type"
UNKNOWN_PROTYPE=" // Failed to retrieve prototype"
UNUSED_SYSCALL_NB=" // Unused syscall"
UNIMPLEMENTED_SYSCALL=" // Unimplemented syscall"

IDENTIFY_TYPE () {
	IFS=' ' read -ra SPLIT <<< "$1"
	TMP=`echo "${SPLIT[-1]}" | grep -E '(\*.*|.*\[[0-9]*\])'`

	# address
	if [ ! -z "$TMP" ]; then
		if [[ "${SPLIT[0]}" == "char" ]]; then
			PTR_NOT_ATTACH_TO_WORD=`echo "$1" | grep -e '.*\* \*' -e '.*\* .*\['`
			IS_MULTI_ARRAY=`echo "${SPLIT[-1]}" | grep -e '\*\*.*' -e '\*.*\['`
			if [ -z "$IS_MULTI_ARRAY" -a -z "$PTR_NOT_ATTACH_TO_WORD" ]; then
				RET_TYPE="T_STR"
				return
			fi
		fi
		RET_TYPE="T_ADDR"
		return
	fi

	# void
	if [[ "${SPLIT[0]}" == "void" ]]; then
		RET_TYPE="T_NONE"
		return
	fi

	# Unknown
	if [[ "${SPLIT[0]}" == "..." ]]; then
		IS_UNKNOWN=true
		RET_TYPE="T_UNKNOWN"
		return
	fi

	# struct
	if [[ "${SPLIT[0]}" == "struct" ]]; then
		RET_TYPE=`echo "T_S_${SPLIT[1]}" | sed -e 's/T_S_*/T_S_/g' | tr [a-z] [A-Z]`
		return
	fi

	# enum
	if [[ "${SPLIT[0]}" == "enum" ]]; then
		RET_TYPE=`echo "T_E_${SPLIT[1]}" | sed -e 's/T_E_*/T_E_/g' | tr [a-z] [A-Z]`
		return
	fi

	# union
	if [[ "${SPLIT[0]}" == "union" ]]; then
		RET_TYPE=`echo "T_U_${SPLIT[1]}" | sed -e 's/T_U_*/T_U_/g' | tr [a-z] [A-Z]`
		return
	fi

	# typedef
	if [ "${SPLIT[0]}" != "unsigned" -a "${SPLIT[0]}" != "long" -a "${SPLIT[0]}" != "int" ]; then
		if [ $COMPILED_GET_REAL_TYPE -eq 0 ]; then
			RET_TYPE=`"$PATH_GET_REAL_TYPE" "${SPLIT[0]}"`
			if [ "$RET_TYPE" == "T_UNKNOWN" ]; then
				IS_UNKNOWN=true
			fi
			return
		fi
		IS_UNKNOWN=true
		RET_TYPE="T_UNKNOWN"
		return
	fi

	# [unsigned] [long] [long] int
	TMP_TYPE="T_"
	LENGTH_SPLIT=${#SPLIT[@]}
	COUNT_SPLIT=0
	while [ $COUNT_SPLIT -lt $LENGTH_SPLIT ]
	do
		if [[ "${SPLIT[$COUNT_SPLIT]}" == "unsigned" ]]; then
			TMP_TYPE+="U"
		elif [[ "${SPLIT[$COUNT_SPLIT]}" == "long" ]]; then
			TMP_TYPE+="L"		
		elif [[ "${SPLIT[$COUNT_SPLIT]}" == "int" ]]; then
			RET_TYPE="$TMP_TYPE""INT"
			return
		fi
		COUNT_SPLIT=$((COUNT_SPLIT+1))
	done
	RET_TYPE="$TMP_TYPE""INT"
	return
}

GEN_SYSCALL_FILE () {
	rm -f "$2"
	SYSCALL_FAIL=
	SYSCALL_PREV_NBR=-1
	while IFS= read -r LINE
	do
		if [[ "$LINE" == "$PATTERN_SYS_NB"* ]]; then
			SYSCALL=`echo "$LINE" | cut -c $((${#PATTERN_SYS_NB} + 1))- | awk '{print $1;}'`
			SYSCALL_NBR=`echo "$LINE" | cut -c $((${#PATTERN_SYS_NB} + 1))- | awk '{print $2;}'`

			# add entry for syscall number with no reference
			if [[ $SYSCALL_NBR != $((SYSCALL_PREV_NBR+1)) ]]; then
				for i in $(eval "echo {"$(($SYSCALL_PREV_NBR+1))".."$(($SYSCALL_NBR-1))"}"); do
					printf "[%3d] = {\"syscall_0x%x\", {T_HEX, T_HEX, T_HEX, T_HEX, T_HEX, T_HEX, T_HEX}, $3},$UNUSED_SYSCALL_NB\n" "$i" "$i" | tee -a $2
				done
			fi
			SYSCALL_PREV_NBR=$SYSCALL_NBR

			#Find if man page exist
			# sudo apt-get install manpages-dev
			MAN_PAGE=`man -P cat 2 "$SYSCALL" 2> /dev/null`
			if [ $? -ne 0 ]; then
				MAN_PAGE=`man -P cat 3 "$SYSCALL" 2> /dev/null`
				if [ $? -ne 0 ]; then
					printf "[%3d] = {\"$SYSCALL\", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LLINT}, $3},$UNKNOWN_PROTYPE\n" "$SYSCALL_NBR" | tee -a $2
					SYSCALL_FAIL+="\n$SYSCALL"
					continue
				fi
			fi


			# Prepare syscall prototype
			SYSCALL=`echo $SYSCALL | sed 's/[36][24]//g'`
			PROTOTYPE=`echo "$MAN_PAGE" \
				| sed -n "/$PATTERN_PROTOTYPE_SECTION_BEG/,/$PATTERN_PROTOTYPE_SECTION_END/p" \
				| sed 's,\/\*.*\*\/,,g' \
				| sed 's/const//g' \
				| sed ':a;N;$!ba;s/,[ ]*\n/, /g' \
				| grep -E ' [_\*]?'"$SYSCALL"'\(..*\);' \
				| grep -v -e 'Note:' -e '=' \
				| tr -s ' '`
			if [ -z "$PROTOTYPE" ]; then
				IS_UNIMPLEMENTED=`echo $MAN_PAGE | cut -c1-"$PATTERN_UNIMPLEMENTED_LENGTH"`
				if [ "$IS_UNIMPLEMENTED" == "$PATTERN_UNIMPLEMENTED" ]; then
					printf "[%3d] = {\"$SYSCALL\", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LLINT}, $3},$UNIMPLEMENTED_SYSCALL\n" "$SYSCALL_NBR" | tee -a $2
				else
					printf "[%3d] = {\"$SYSCALL\", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LLINT}, $3},$UNKNOWN_PROTYPE\n" "$SYSCALL_NBR" | tee -a $2
				fi
				SYSCALL_FAIL+="\n$SYSCALL"
				continue
			fi


			# Remove multiple prototype for same syscall
			NB_LINE=`echo "$PROTOTYPE" | wc -l`
			if [ $NB_LINE -gt 1 ]; then
				MAX_ARG=0
				GOOD_FUNC=
				while IFS= read -r FUNC
				do
					ARGS=`echo "$FUNC" | awk -F'[()]' '{print $2}'`
					IFS=' ' read -ra ARRAY_ARG <<< "$ARGS"
					if [ ${#ARRAY_ARG[@]} -gt $MAX_ARG ]; then
						GOOD_FUNC=$FUNC
					fi
				done <<< "$PROTOTYPE"
				PROTOTYPE=$GOOD_FUNC
			fi


			# Generate our syscall prototype
			PRINT_PROTOTYPE=`printf "[%3d] = {\"$SYSCALL\", {" "$SYSCALL_NBR"`
			ARGS=`echo "$PROTOTYPE" | awk -F'[()]' '{print $2}'`
			IFS=',' read -ra ARRAY_ARG <<< "$ARGS"
			COUNT_ARG=0
			for ARG in "${ARRAY_ARG[@]}"
			do
				RET_TYPE="T_NONE"
				IS_UNKNOWN=false
				IDENTIFY_TYPE "$ARG"
				if [ $COUNT_ARG -gt 0 ]; then
					PRINT_PROTOTYPE+=", $RET_TYPE"
				else
					PRINT_PROTOTYPE+="$RET_TYPE"
				fi
				COUNT_ARG=$((COUNT_ARG+1))
			done
			if [ "$COUNT_ARG" -lt 6 ]; then
				PRINT_PROTOTYPE+=`printf '%0.s, T_NONE' $(eval "echo {1.."$((6-COUNT_ARG))"}")`
			fi
			RET_VAL=`echo "$PROTOTYPE" | sed 's/[(].*//g'`
			IDENTIFY_TYPE "$RET_VAL"
			PRINT_PROTOTYPE+=", $RET_TYPE"
			if [ "$IS_UNKNOWN" = true ]; then
				SYSCALL_FAIL+="\n$SYSCALL"
				PRINT_PROTOTYPE+="}, $3},$UNKNOWN_ARG\n"
			else
				PRINT_PROTOTYPE+="}, $3},\n"
			fi
			printf "$PRINT_PROTOTYPE" | tee -a $2
		fi
	done < "$1"

	if [ ! -z "$SYSCALL_FAIL" ]; then
		printf "\n$0: warning: can't partially or fully identify these syscalls: $SYSCALL_FAIL\n"
	fi
}

GEN_SYSCALL_FILE $UNISTD_32 $OUTPUT_32 $HANDLER_32
printf '\n--------------------------------------\n\n'
GEN_SYSCALL_FILE $UNISTD_64 $OUTPUT_64 $HANDLER_64