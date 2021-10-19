import gdb

m = -100
n = 100
s = 3

break_line = 34

gdb.execute(command=f'file range', to_string=True)
gdb.execute(command=f'break {break_line}', to_string=True)
gdb.execute(command=f'run {m} {n} {s} > /dev/null', to_string=True)

count = 0
while True:
    try:
        value = gdb.parse_and_eval('I.value')
    except gdb.error:
        gdb.execute(command='q', to_string=True)

    start = gdb.parse_and_eval('I.start')
    stop = gdb.parse_and_eval('I.stop')
    step = gdb.parse_and_eval('I.step')

    count += 1

    if count in range(28, 36):
        print(f'@@@ {start} {stop} {step} {value}')

    gdb.execute(command='c', to_string=True)
