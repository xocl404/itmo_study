import numpy
import matplotlib.pyplot

m = float(input("Введите массу тела (кг): "))
R = float(input("Введите радиус кольца (м): "))
a = float(input("Введите угловой размер дуги (в радианах, от \u03c0/2 до 3\u03c0/2): "))
mu = float(input("Введите коэффициент трения: "))
g = 9.81  # Ускорение свободного падения
# Вычисления
cos_a = numpy.cos(a)
sin_a = numpy.sin(a)
height = R * (1 - cos_a)  # Высота относительно нижней точки
work_friction = mu * m * g * R * a  # Работа силы трения
# Энергетический расчет скорости
potential_energy = m * g * height
kinetic_energy = potential_energy + work_friction
v_initial = numpy.sqrt(2 * kinetic_energy / m)
print(f"Необходимая начальная скорость: {v_initial:.2f} м/с")
# Движение на дуге
angles = numpy.linspace(0, a, num=100)
x_arc = R * numpy.sin(angles)  # Горизонтальная координата на дуге
y_arc = R * (1 - numpy.cos(angles))  # Вертикальная координата на дуге
# Скорость при сходе с дуги
v_x_end = v_initial * cos_a  # Горизонтальная составляющая скорости
v_y_end = v_initial * sin_a  # Вертикальная составляющая скорости
# Движение после отрыва
t_flight = (v_y_end + numpy.sqrt(v_y_end**2 + 2 * g * height)) / g  # Время полета
t = numpy.linspace(0, t_flight, num=100)  # Дискретные моменты времени
x_flight = R * numpy.sin(a) + v_x_end * t  # Горизонтальная координата
y_flight = height + v_y_end * t - 0.5 * g * t**2  # Вертикальная координата

# Построение графика
matplotlib.pyplot.figure(figsize=(10, 8))
# Траектория на дуге
matplotlib.pyplot.plot(x_arc, y_arc, label='Траектория на дуге', color='g')
# Траектория после отрыва
matplotlib.pyplot.plot(x_flight, y_flight, label='Траектория после отрыва', color='b')
matplotlib.pyplot.scatter(x_arc[-1], y_arc[-1], color='r', zorder=5, label='Точка отрыва')

matplotlib.pyplot.title("Траектория тела на дуге и после отрыва")
matplotlib.pyplot.xlabel("Горизонтальная координата, м")
matplotlib.pyplot.ylabel("Вертикальная координата, м")
matplotlib.pyplot.axhline(0, color='black', lw=1)
matplotlib.pyplot.legend()
matplotlib.pyplot.grid()
matplotlib.pyplot.show()
