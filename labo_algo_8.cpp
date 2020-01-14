#include <fstream>
#include <iostream>
#include <string>
#include "list.h"
#include "heap.h"
#include "DynamicArray.h"
#include "point.h"
#include <time.h>

clock_t start;
clock_t end;
double sorting_time;
double algorithm_time;

DynamicArray<point> parseFile(std::string path)
{
	std::ifstream input_file;
	DynamicArray<point> tab;
	input_file.open(path);
	
	int i = 0; 
	input_file >> i;
	int k = i;
	double x=0.0, y=0.0;
	for (; i > 0; i--)
	{
		input_file >> x >> y;
		tab.add(point(x, y,k-i));
	}
	return tab;
}

inline bool cmp(point obj1, point obj2)
{
	return (((obj1.y * obj2.x) - (obj2.y * obj1.x)) <= 0.0);
}

inline bool equal(point obj1, point obj2)
{
	return (obj1.x == obj2.x && obj1.y == obj2.y);
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
	std::cout << obj.index << " | " << obj.x << " , " << obj.y << std::endl;
}

void printer2(const point obj)
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

point sub_points(point obj1, point obj2)
{
	return point(obj1.x - obj2.x, obj1.y - obj2.y,obj1.index);
}

list<point> graham_scan(DynamicArray<point> tab)
{
	list<point> convex_hull;
	//std::cout << std::endl;
	point p0 = tab.get_max_min(smallest_point);
	tab.remove(p0,equal);
	/*printer(start);
	std::cout << std::endl;*/
	//tab.print(printer);
	//std::cout << std::endl;
	for (int i = 0; i < tab.get_current_size(); i++)
	{
		tab[i] = sub_points(tab[i], p0);
	}

	start = clock();
	heap_sort_inplace<point>(tab, cmp);
	end = clock();
	sorting_time = (double(end) - double(start)) / CLOCKS_PER_SEC;
	//tab.print(printer);
	
	convex_hull.add_tail(p0);
	convex_hull.add_tail(tab[0]);
	/*convex_hull.print(printer);
	std::cout << std::endl;*/
	int stop = (int)tab.get_current_size();
	int i = 1;
	//convex_hull.remove_position(1);
	//convex_hull.print(printer);
	std::cout << std::endl;
	for (int k = 1; k <= stop; k++)
	{
		convex_hull.add_tail(tab[k]);
		while (!cmp(sub_points(convex_hull.get_element((long long)(i - 1)), convex_hull.get_element(i)),sub_points(convex_hull.get_element(i), convex_hull.get_element((long long)(i + 1)))))
		{
			convex_hull.remove_position(i);
			i--;
		}
		i++;
		/*convex_hull.print(printer);
		std::cout << std::endl;*/
	}

	return convex_hull;
}

int main()
{
	DynamicArray<point> points = parseFile("points5.txt");	
	DynamicArray<point> points2 = points.copy();
	//points2.print(printer);
	//std::cout << std::endl;

	start = clock();
	list<point> powloka = graham_scan(points2);
	end = clock();
	algorithm_time = (double(end) - double(start)) / CLOCKS_PER_SEC;

	std::cout << "Czas sortowania: " << sorting_time << " | Czas pracy algorytmu: " << algorithm_time-sorting_time << std::endl;
	std::cout << "Liczba punktow w powloce: " << powloka.get_size() << " | Indeksy punktow powloki: " << std::endl;
	powloka.print(printer2);
}