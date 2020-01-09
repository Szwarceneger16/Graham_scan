#include <fstream>
#include <iostream>
#include <string>
#include "list.h"
#include "heap.h"
#include "DynamicArray.h"
#include "point.h"
#include <time.h>


DynamicArray<point> parseFile(std::string path)
{
	std::ifstream input_file;
	DynamicArray<point> tab;
	input_file.open(path);
	
	int i = 0; 
	input_file >> i;
	double x=0.0, y=0.0;
	for (; i > 0; i--)
	{
		input_file >> x >> y;
		tab.add(point(x, y,i));
	}
	return tab;
}

bool static cmp(point obj1, point obj2)
{
	double product = (obj1.y * obj2.x) - (obj2.y * obj1.x);
	if (product == 0.0)
		return (obj1.x < obj2.x);
	return (product < 0.0);
}

bool static smallest_point(point obj1, point obj2)
{
	if (obj1.y < obj2.y) return false;
	else if(obj1.y > obj2.y) return true;
	else
	{
		if (obj1.x < obj2.x) return true;
		else return false;
	}
}

void static printer(const point obj)
{
	std::cout << obj.x << " , " << obj.y << std::endl;
}

void static printer2(const point obj)
{
	static int wiersz = 0;
	if (wiersz == 10)
	{
		wiersz = 0;
		std::cout << std::endl;
	}
	std::cout << obj.index << " , " ;
	wiersz++;
}

inline point static sub_points(point obj1, point obj2)
{
	return point(obj2.x - obj1.x, obj2.y - obj1.y);
}

list<point> graham_scan(DynamicArray<point> tab)
{
	list<point> convex_hull;
	//std::cout << std::endl;
	point p0 = tab.find(smallest_point);
	/*printer(start);
	std::cout << std::endl;*/
	//tab.print(printer);
	//std::cout << std::endl;
	
	convex_hull.add_tail(p0);
	convex_hull.add_tail(tab[0]);
	/*convex_hull.print(printer);
	std::cout << std::endl;*/
	int stop = (int)tab.get_current_size();
	int i = 1;
	for (int k = 1; k <= stop; k++)
	{
		convex_hull.add_tail(tab[k]);
		if (cmp(sub_points(convex_hull.get_element((long long)(i + 1)), convex_hull.get_element(i)), sub_points(convex_hull.get_element(i), convex_hull.get_element((long long)(i - 1)))))
		{
			convex_hull.remove_position(i);
		}
		else i++;
		/*convex_hull.print(printer);
		std::cout << std::endl;*/
	}

	return convex_hull;
}

clock_t start;
clock_t end;
double sorting_time;
double algorithm_time;

int main()
{
	DynamicArray<point> points = parseFile("points5.txt");	
	DynamicArray<point> points2 = points.copy();
	//points.print(printer);
	//std::cout << std::endl;

	start = clock();
	heap_sort_inplace<point>(points2, cmp);
	end = clock();
	sorting_time = (double(end) - double(start)) / CLOCKS_PER_SEC;

	start = clock();
	list<point> powloka = graham_scan(points2);
	end = clock();
	algorithm_time = (double(end) - double(start)) / CLOCKS_PER_SEC;

	std::cout << "Czas sortowania: " << sorting_time << " | Czas pracy algorytmu: " << algorithm_time << std::endl;
	std::cout << "Liczba punktow w powloce: " << powloka.get_size() << " | Indeksy punktow powloki: " << std::endl;
	powloka.print(printer2);
}