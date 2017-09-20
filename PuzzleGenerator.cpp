#include "PuzzleGenerator.h"
#include <cmath>
#include <cstdlib>
using namespace std;

PuzzleGenerator::PuzzleGenerator(int _nRows, int _nColumns, int _minVal, int _maxVal)
	:nRows(_nRows), nColumns(_nColumns), minVal(_minVal), maxVal(_maxVal)
{}

Puzzle PuzzleGenerator::GeneratePuzzle()
{
	timer.StartTimer();
	maxtime = 59.9;	// To make sure we don't exceed a minute
	
	//return RandomWalk(5);	// Do a random walk for 5 seconds and return the solution.
   Puzzle p = RandomWalk(.01);
	// We could also do as many random walks as we can within the given time limit.
   Puzzle best = p;

	while (timer.GetElapsedTime() + 3 < maxtime)
	{
		p = RandomWalk(3);
		if(p.GetValue() > best.GetValue()){
			best = p;
		}
		// Check if p is better than the best puzzle we have found so far.
	}
	return best;
}

Puzzle PuzzleGenerator::RandomWalk(double timelimit)
{
	// A very simple function that starts at a random configuration and keeps randomly modifying it
	// until the time limit is reached. Returns the best solution found so far.

	Puzzle p(nRows, nColumns, minVal, maxVal);	// Generate a random puzzle with the specified values.
	
	// Keep track of the best puzzle found so far (and its value).
	Puzzle bestPuzzle = p;			
	Puzzle temp = p;

	int bestValue = p.GetValue();
	
	// Keep track of the time so we don't exceed it.
	Timer t;
	t.StartTimer();

	
	double delta;
	double anneal;
	double te;
	double ideal = nRows*nColumns*maxVal*5;



	while (t.GetElapsedTime() < timelimit-0.1)	// To make sure that we don't exceed the time limit, we stop just before we hit the time limit.
	{
	
		te = ideal - bestValue;
		te = te/ideal;
		temp = p.GetRandomSuccessor();
		delta = (double)temp.GetValue() - (double)p.GetValue();
		if(delta > 0){
			p = temp;
			bestValue = p.GetValue();
		}
		else{

			anneal = exp(delta/te);	
			double ran;
			ran = (double)rand()/(double)RAND_MAX;
			if (ran < anneal)
			{
				p = temp;
				bestValue = p.GetValue();
			}
		}
	

	if (bestValue > bestPuzzle.GetValue())
		{
			bestPuzzle = p;
		}

	}
		cout << "best vale" << bestPuzzle.GetValue() << endl;
		return bestPuzzle;
}
