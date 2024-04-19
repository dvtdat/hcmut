#include <iostream>
#include <cmath>
using namespace std;

double areaSquare(double side) {
    return side * side;
}

double areaRectangle(double length, double width) {
    return length * width;
}

double areaCircle(double radius) {
    return M_PI * radius * radius;
}

double areaTriangle(double base, double height) {
    return 0.5 * base * height;
}

int main() {
    int choice;
    double side, length, width, radius, base, height;

    while (true) {
        cout << "Choose a shape to calculate its area:\n";
        cout << "1. Square\n";
        cout << "2. Rectangle\n";
        cout << "3. Circle\n";
        cout << "4. Triangle\n";
        cout << "Enter your choice (1-4, or -1 to exit): ";
        cin >> choice;

        if (choice == -1) {
            cout << "Exiting program...\n";
            break;
        }

        switch (choice) {
            case 1:
                cout << "Enter the side length of the square: ";
                cin >> side;
                cout << "Area of the square: " << areaSquare(side) << endl;
                break;
            case 2:
                cout << "Enter the length of the rectangle: ";
                cin >> length;
                cout << "Enter the width of the rectangle: ";
                cin >> width;
                cout << "Area of the rectangle: " << areaRectangle(length, width) << endl;
                break;
            case 3:
                cout << "Enter the radius of the circle: ";
                cin >> radius;
                cout << "Area of the circle: " << areaCircle(radius) << endl;
                break;
            case 4:
                cout << "Enter the base length of the triangle: ";
                cin >> base;
                cout << "Enter the height of the triangle: ";
                cin >> height;
                cout << "Area of the triangle: " << areaTriangle(base, height) << endl;
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}

