#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <cassert>
#include <vector>
#include <assert.h>
#include <iostream>
#include <exception>
using namespace std;
bool rel1(TComp r1, TComp r2) 
{
    return r1 <= r2;
}
void test_removeAll()
{
    cout << "\nTest remove all\n";
    SortedBag sb(rel1);

    sb.add(1);
    sb.add(2);
    sb.add(2);
    sb.add(3);
    sb.add(3);
    sb.add(3);

    assert(sb.nrOccurrences(1) == 1);
    assert(sb.nrOccurrences(2) == 2);
    assert(sb.nrOccurrences(3) == 3);

    int removedCount = sb.removeAll();

    assert(removedCount == 5); // 2 occurrences of 2 + 3 occurrences of 3
    assert(sb.nrOccurrences(1) == 1);
    assert(sb.nrOccurrences(2) == 0);
    assert(sb.nrOccurrences(3) == 0);

    sb.add(1);
    sb.add(2);
    sb.add(2);
    sb.add(3);
    sb.add(3);
    sb.add(3);
    sb.add(3);

    assert(sb.nrOccurrences(1) == 2);
    assert(sb.nrOccurrences(2) == 2);
    assert(sb.nrOccurrences(3) == 4);

    removedCount = sb.removeAll();

    assert(removedCount == 8); // 2 occurrences of 2 + 4 occurrences of 3
    assert(sb.nrOccurrences(1) == 0);
    assert(sb.nrOccurrences(2) == 0);
    assert(sb.nrOccurrences(3) == 0);

    sb.add(4);
    sb.add(4);
    sb.add(4);

    assert(sb.nrOccurrences(4) == 3);

    removedCount = sb.removeAll();

    assert(removedCount == 3); // 3 occurrences of 4
    assert(sb.nrOccurrences(1) == 0);
    assert(sb.nrOccurrences(4) == 0);


    SortedBag emptySB(rel1);//empty bag
    removedCount = emptySB.removeAll();//  remove all from empty bag
    assert(removedCount == 0);
}
int main() {
	testAll();
	testAllExtended();
	test_removeAll();
	cout << "\nTest over\n" << endl;
	system("pause");
}
