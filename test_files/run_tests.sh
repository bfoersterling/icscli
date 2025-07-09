#!/bin/bash

mapfile -t files < <(find ../tests/. -name "*.ics")

i=1
for file in ${files[@]}; do
	echo "TEST ${i}: ${file}"
	echo "===================================================="
	../src/icscli -f "${file}"
	echo "===================================================="
	echo
	((i++))
done

exit 0
