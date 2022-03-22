// TreeSetup.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <list>
#include "PreBalanceTree.h"

using namespace std;

int main()
{
	Tree<int> tTreeOne;
	tTreeOne.SetDebug( true );

	tTreeOne.Add( 50 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 30 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 80 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 90 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 100 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 60 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 20 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 10 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 15 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 55 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 110 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 120 );
	tTreeOne.Dump( nullptr );
	// I bet drawing that out on paper first would help.

	if( tTreeOne.Contains( 15 ) )
		cout << "Check 1" << endl;
	if( tTreeOne.Contains( 50 ) )
		cout << "Check 2" << endl;
	if( tTreeOne.Contains( 60 ) )
		cout << "Check 3" << endl;
	if( tTreeOne.Contains( 110 ) )
		cout << "Check 4" << endl;
	if( !tTreeOne.Contains( 99 ) )
		cout << "Check 5" << endl;

	Tree<int> tTreeTwo( tTreeOne );
	tTreeOne.Remove( 90 );
	if( tTreeTwo.Contains( 90 ) )
		cout << "Check 6" << endl;

	Tree<int> tTreeThree;
	tTreeThree.Add( 999 );
	tTreeThree = tTreeOne;
	tTreeOne.Remove( 20 );
	if( tTreeThree.Contains( 20 ) )
		cout << "Check 7" << endl;
	if( !tTreeThree.Contains( 999 ) )
		cout << "Check 8" << endl;
	if( !tTreeOne.Contains( 20 ) )
		cout << "Check 9" << endl;

	tTreeOne.Add( 90 );
	if( tTreeOne.Contains( 90 ) )
		cout << "Check 10" << endl;

	//std::list<int> tOneFlattened;
	//tTreeOne.Dump( &tOneFlattened );
	//for( auto iter = tOneFlattened.begin(); iter != tOneFlattened.end(); ++iter )
	//	cout << (*iter) << " ";
	//cout << endl;
	tTreeOne.SetDebug( true );
	tTreeOne.Dump(nullptr);

	return 0;
}

