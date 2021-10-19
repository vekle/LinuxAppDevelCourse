import gdb

m = 1
n = 12

break_line = 34

gdb.execute(command=f'file range', to_string=True)
gdb.execute(command=f'break {break_line}', to_string=True)
gdb.execute(command=f'run {m} {n} > /dev/null', to_string=True)

while True:
    try:
        value = gdb.parse_and_eval('I.value')
    except gdb.error:
        gdb.execute(command='q', to_string=True)

    start = gdb.parse_and_eval('I.start')
    stop = gdb.parse_and_eval('I.stop')
    step = gdb.parse_and_eval('I.step')

    if value % 5 == 0:
        print(f'@@@ {start} {stop} {step} {value}')

    gdb.execute(command='c', to_string=True)
