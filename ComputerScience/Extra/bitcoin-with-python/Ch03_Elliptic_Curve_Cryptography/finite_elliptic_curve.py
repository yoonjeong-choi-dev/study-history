from ecc.finite_field import FiniteFieldElement, generate_finite_field
from ecc.elliptic_curve_point import Point
from unittest import TestCase


class ECCTest(TestCase):
    def test_on_curve(self):
        prime = 223
        field = generate_finite_field(prime)

        a = field(0)
        b = field(7)

        valid_points = [
            (192, 105),
            (17, 56),
            (1, 193),
        ]
        invalid_points = [
            (200, 119),
            (42, 99)
        ]

        # valid test
        for x_raw, y_raw in valid_points:
            x = field(x_raw)
            y = field(y_raw)
            Point(x, y, a, b)

        # invalid test
        for x_raw, y_raw in invalid_points:
            x = field(x_raw)
            y = field(y_raw)
            with self.assertRaises(ValueError):
                Point(x, y, a, b)

    # Exercise3
    def test_add(self):
        finite223 = generate_finite_field(223)
        point_list = [
            (170, 142),
            (60, 139),
            (47, 71),
            (17, 56),
            (143, 98),
            (76, 66)
        ]

        points = [(finite223(point[0]), finite223(point[1])) for point in point_list]

        a = finite223(0)
        b = finite223(7)

        answer_list_raw = [
            (220,181), (215,68), (47,71)
        ]
        answer_elements = [(finite223(point[0]), finite223(point[1])) for point in answer_list_raw]
        answer_list = [Point(*point, a, b) for point in answer_elements]

        for i in range(3):
            point1 = Point(*points[2 * i], a, b)
            point2 = Point(*points[2 * i + 1], a, b)
            self.assertEqual(point1+point2, answer_list[i])


def exercise1():
    finite223 = generate_finite_field(223)
    point_list = [
        (192, 105),
        (17, 56),
        (200, 119),
        (1, 193),
        (42, 99)
    ]

    point_field_list = [(finite223(point[0]), finite223(point[1])) for point in point_list]

    a = finite223(0)
    b = finite223(7)

    for point in point_field_list:
        try:
            print(Point(*point, a, b))
        except ValueError as e:
            print(e)

def exercise2():
    finite223 = generate_finite_field(223)
    point_list = [
        (170,142),
        (60,139),
        (47,71),
        (17,56),
        (143,98),
        (76,66)
    ]

    points = [(finite223(point[0]), finite223(point[1])) for point in point_list]

    a = finite223(0)
    b = finite223(7)

    for i in range(3):
        point1 = Point(*points[2*i], a, b)
        point2 = Point(*points[2*i+1], a, b)
        print("{} + {} = ".format(point_list[2*i], point_list[2*i+1]))
        print(point1+point2)



def exercise4():
    finite223 = generate_finite_field(223)
    point_list_raw = [
        (192,105),
        (143,98),
        (47, 71),
        (47,71),
        (47,71),
        (47,71)
    ]

    scalar_list = [2, 2, 2, 4, 8, 21]

    points = [(finite223(point[0]), finite223(point[1])) for point in point_list_raw]

    a = finite223(0)
    b = finite223(7)

    for i in range(len(points)):
        print("{}*{} = ".format(scalar_list[i], point_list_raw[i]))
        point = Point(*points[i], a, b)
        print(scalar_list[i] *point)


def example1():
    field = generate_finite_field(223)
    a = field(0)
    b = field(7)
    x = field(47)
    y = field(71)
    p = Point(x,y,a,b)

    for s in range(1, 21):
        result = s*p
        print("{}*(47, 71) = ({}, {})".format(
            s, result.x.num, result.y.num
        ))


def exercise5():
    field = generate_finite_field(223)
    a = field(0)
    b = field(7)
    x = field(15)
    y = field(86)
    p = Point(x,y,a,b)
    gen_p = p

    print("{} generates...".format(p))
    while True:
        print(gen_p)
        gen_p += p

        if gen_p == p:
            break








if __name__ == "__main__":
    print("Chapter 3-1. Elliptic Curve in Finite Field")
    #exercise1()
    #run_test_case(ECCTest("test_on_curve"))
    #exercise2()
    #exercise3()
    #exercise4()
    #example1()
    exercise5()