#! /bin/sh

program=./rpncalc
fail=0

t() {
    # Usage: t <PROGRAM> <SUPPOSED OUTPUT>

    input="$1"
    supposed_output="$2"
    echo -n "testing: '$input' => '$supposed_output' ... "

    output="$("$program" --eval "$input")"

    if [ "x$supposed_output" == "x$output" ]
    then
        echo 'success.'
    else
        echo "FAILURE, output was '$output'."
        fail=1
        return 1
    fi
}

make "$program"

t '1 2 + .' '3'
t '1 2 - .' '-1'
t '1 -2 - .' '3'
t '1 2 neg - .' '3'
t '1/2 7/6 + .' '5/3'
t '123/456 -17/136 + .' '11/76'
t '123/456 -17/136 neg - .' '11/76'

t '2 3 * .' '6'
t '2 -3 * .' '-6'
t '2 neg -3 * .' '6'
t '2 3/1 * .' '6'
t '6 1/2 * .' '3'

t '6 2 / .' '3'
t '6 -3 / .' '-2'
t '2 1/3 / .' '6'
t '-2 -1/3 / .' '6'

t '4 sqrt .' '2'
t '81 sqrt .' '9'

t '1/2 float .' '0.5'

t 'pi sin round .' '0'


if [ $fail == 0 ]
then
    echo 'All tests passed.'
else
    echo 'SOME TESTS FAILED.'
fi
