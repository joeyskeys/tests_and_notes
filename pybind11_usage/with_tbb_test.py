import sys, os
p = os.path.abspath(os.path.join(os.path.dirname(__file__), '../build/pybind11_usage'))
sys.path.append(p)

import with_tbb as wt

class Dog(wt.Animal):
    def make_noise(self):
        print('woof')


class Cat(wt.Animal):
    def make_noise(self):
        print('meow')


if __name__ == '__main__':
    dog = Dog()
    zoo = wt.Zoo(dog)
    zoo.make_noises()
    print('end of python code')