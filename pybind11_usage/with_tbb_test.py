import sys
sys.path.append('/home/joeys/Desktop/repos/tests_and_notes/build/pybind11_usage')

import with_tbb as wt

class Dog(wt.Animal):
    def make_noise(self):
        print('woof')


class Cat(wt.Animal):
    def make_noise(self):
        print('meow')


if __name__ == '__main__':
    zoo = wt.Zoo()
    for i in range(6):
        zoo.add_animal(Dog())
        zoo.add_animal(Cat())

    zoo.make_noises()