#include <iostream>
#include <ctime>

template <typename T>
class PrioritizedObject
{
	int priority;
	T value;
	template <typename T> friend class PriorityStack;
};

//необходимо реализовать стэк с приоритетами.
//Должен соблюдаться LIFO - порядок для элементов с одинаковым приоритетом.
//Реализовать программу, демонстрирующую корректность работы стэка.
//Интерфейс должен быть следующим :
template <typename T>
class PriorityStack
{
	PrioritizedObject<T>* stArray = new PrioritizedObject<T>[size];
	int size = 0;

public:
	~PriorityStack()
	{
		if (size != 0)
		{
			delete[] stArray;
			stArray = nullptr;
		}
	}
	// добавить элемент в стэк
	void Push(const int& priority, const T& value)
	{
		PrioritizedObject<T>* tempArray = stArray;

		stArray = new PrioritizedObject<T>[++size];

		for (size_t i = 0; i < size - 1; ++i)
		{
			stArray[i] = tempArray[i];
		}

		stArray[size - 1].priority = priority;
		stArray[size - 1].value = value;

		delete[] tempArray;
		tempArray = nullptr;
	}

	// взять элемент из стэка с максимальным приоритетом
	T Pop()
	{
		if (size == 0)
		{
			std::cout << "there is no elements in stack to delete\n";
			return T();
		}

		PrioritizedObject<T>* pPrioritized = stArray + size - 1;
		for (int i = size - 1; i >= 0; --i)
		{
			if (stArray[i].priority > pPrioritized->priority)
			{
				pPrioritized = (stArray + i);
			}
		}

		PrioritizedObject<T>* tempArray = stArray;
		stArray = new PrioritizedObject<T>[--size];

		int i = 0;
		while (true)
		{
			if (pPrioritized == (tempArray + i))
			{
				break;
			}
			stArray[i] = tempArray[i];
			++i;
		}
		while (i < size)
		{
			stArray[i] = tempArray[i + 1];
			++i;
		}

		T forReturn = pPrioritized->value;

		delete[] tempArray;
		tempArray = nullptr;

		return forReturn;
	}

	// проверяет, пустой ли стэк
	bool IsEmpty()
	{
		return size == 0;
	}

	// очищает стэк
	void Clear()
	{
		delete[] stArray;
		size = 0;
	}

	void ShowAll()
	{
		if (size < 1)
		{
			std::cout << "there is no elements in stack to show\n";
		}
		for (size_t i = 0; i < size; ++i)
		{
			std::cout << stArray[i].value << "\t|\t" << stArray[i].priority << std::endl;
		}
		std::cout << std::endl;
	}
};

int main()
{
	PriorityStack<int> priority_stack;

	srand(time(NULL));

	for (size_t i = 0; i < 5; ++i)
	{
		priority_stack.Push(rand() % 3, rand() % 25);
	}

	priority_stack.ShowAll();

	for (size_t i = 0; i < 3; ++i)
	{
		priority_stack.Pop();
		priority_stack.ShowAll();
	}

	priority_stack.Push(0, 111);
	priority_stack.ShowAll();

	priority_stack.Pop();
	priority_stack.ShowAll();

	std::cout << "Is empty - " << priority_stack.IsEmpty() << std::endl;
	priority_stack.Clear();
	std::cout << "Is empty - " << priority_stack.IsEmpty() << std::endl;

	return 0;
}