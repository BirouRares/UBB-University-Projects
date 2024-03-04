#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"
#include <assert.h>

using namespace std;
void test_mostFrequent()
{
    cout<<"Test mostFrequent\n";
    MultiMap multiMap;

    //empty MultiMap
    TValue mostFrequentValue = multiMap.mostFrequent();
    assert(mostFrequentValue == NULL_TVALUE);

    //multiple key-value pairs
    multiMap.add(1, 5);
    multiMap.add(2, 10);
    multiMap.add(2, 10);
    multiMap.add(2, 15);
    multiMap.add(3, 15);
    multiMap.add(3, 15);

    mostFrequentValue = multiMap.mostFrequent();
    assert(mostFrequentValue == 15);

    //multiple most frequent values
    multiMap.add(4, 5);
    multiMap.add(4, 10);
    multiMap.add(4, 10);
    multiMap.add(4, 15);

    mostFrequentValue = multiMap.mostFrequent();
    assert(mostFrequentValue == 10 || mostFrequentValue == 15);
}

int main() {


	testAll();
	testAllExtended();
    test_mostFrequent();
	cout << "End" << endl;
	system("pause");

}
