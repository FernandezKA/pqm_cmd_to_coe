Данная утилита используется для преобразования существующей системы команд (их мнемоник) в набор чисел, предназначенных для инициализации BRAM памяти путем задания .COE файла.

После старта программы необходимо указать путь до считываемого файла с командами, а также до записываемого файла. Путь необходимо указывать с расширением, в случае, если записываемый файл не существует, он будет создан.

В настоящий момент поддерживаются следующие мненомники:

GEW - gpio external write
GES - gpio external set
GER - gpio external reset
GIW - gpio internal write
GIS - gpio internal set
GIR - gpio internal reset
SAMP - set amplitude
SZFC - set zero frequency carrier
SZFR - set zero frequency rotator
SFIC - set frequency increment carrier
SFIR - set frequency increment rotator
SPC - set phase carrier
SPR - set phase rotator
JMP - jump to label
AJMP - absolute jmp
NOP - no of operations
SMOD - set modulation mode

В случае обнаружения некорректной мненомники будет выведено предупреждающее сообщение. Процесс обработки сопровождается полным выводом пошаговой информации обработки. 
