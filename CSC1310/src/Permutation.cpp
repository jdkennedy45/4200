#include "Permutation.h"
using CSC1310::Permutation;

#include "ListArrayIterator.h"

#include <iostream>

#include "ReadFile.h"
#include "WriteFile.h"

void Permutation::generatePermutation()
{
	clearPermutation();
	ListArray<Integer>* numbers = new ListArray<Integer>();
	for (int i = 1; i <= n; i++)
	{
		Integer* num = new Integer(i);
		numbers->add(num);
	}
	
	Random* random = Random::getRandom();
	permutation = new ListArray<Integer>();
	
	while(numbers->size() > 0)
	{
		int index = random->getRandomInt(1, numbers->size());
		Integer* num = numbers->get(index);
		permutation->add(num);
		numbers->remove(index);
	}
	
	delete numbers;  //should be empty
}

void Permutation::writeFile(String& file_name)
{
	ListArray<Integer>* numbers = new ListArray<Integer>();
	for (int i = 1; i <= n; i++)
	{
		Integer* num = new Integer(i);
		numbers->add(num);
	}
	
	Random* random = Random::getRandom();
	
	WriteFile* wf = new WriteFile(file_name.get_c_str());
	while(numbers->size() > 0)
	{
		int index = random->getRandomInt(1, numbers->size());
		Integer* num = numbers->get(index);
		int value = num->getValue();
		String value_str = String::i_to_a(value);
		wf->writeLine(&value_str);
		numbers->remove(index);
	}
	wf->close();
	delete wf;
	
	delete numbers;  //should be empty
}

void Permutation::readFile(String& file_name)
{
	clearPermutation();
	permutation = new ListArray<Integer>();
	
	ReadFile* rf = new ReadFile(file_name.get_c_str());
	String* line = rf->readLine();
	while(!rf->eof())
	{
		int i = line->a_to_i();
		Integer* num = new Integer(i);
		permutation->add(num);
		delete line;
		line = rf->readLine();
	}
	rf->close();
	delete rf;
}

Permutation::Permutation(int r_, int n_)
{
   r = r_;
   n = n_;
   permutation = NULL;
}

void Permutation::clearPermutation()
{
	if (permutation != NULL)
	{
		ListArrayIterator<Integer>* permute_iter = permutation->iterator();
		while(permute_iter->hasNext())
		{
			Integer* i = permute_iter->next();
			delete i;
		}
		delete permute_iter;
		delete permutation;
	}
	permutation = NULL;
}

Permutation::~Permutation()
{
	clearPermutation();
}

bool Permutation::hasNext()
{
	return (r > 0);
}

int Permutation::next()
{
	if (r == 0) return 0;
   
	Integer* permute = permutation->get(1);
	int value = permute->getValue();
	permutation->remove(1);
	delete permute;
   
	r--;
	return value;
}
