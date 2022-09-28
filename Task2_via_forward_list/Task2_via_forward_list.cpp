#include <iostream>

template <typename T>
class PrioritizedObject
{
	int priority;
	T value;
	PrioritizedObject* pNextObject;

	template <typename T>
	friend class PriorityStack;

public:
	PrioritizedObject(int priority, T value, PrioritizedObject* pNextObject = nullptr)
	{
		this->priority = priority;
		this->value = value;
		this->pNextObject = pNextObject;
	}
};

template <class T>
class PriorityStack
{
	PrioritizedObject<T>* head = nullptr;
	int size = 0;

public:
	// добавить элемент в стэк
	void Push(int priority, T value)
	{
		if (head == nullptr)
		{
			this->head = new PrioritizedObject<T>(priority, value);
		}
		else
		{
			PrioritizedObject<T>* currentPtr = this->head;
			while (currentPtr->pNextObject != nullptr)
			{
				currentPtr = currentPtr->pNextObject;
			}
			currentPtr->pNextObject = new PrioritizedObject<T>(priority, value);
		}
		++size;
	}
	// взять элемент из стэка с максимальным приоритетом
	T Pop()
	{
		if (size == 0)
		{
			std::cout << "there is no elements in stack to delete\n";
			return T();
		}
		else if (size == 1)
		{
			/*PrioritizedObject<T>* temp = this->head;
			this->head = this->head->pNextObject;*/
			T toReturn = head->value;
			delete head;
			head = nullptr;
			--size;
			return toReturn;
		}
		else
		{
			PrioritizedObject<T>* toDelete = this->head;
			PrioritizedObject<T>* current = this->head;
			PrioritizedObject<T>* previous = this->head;

			for (int i = 0; i < size - 1; ++i)
			{
				if (toDelete->priority <= current->pNextObject->priority)
				{
					previous = current;
					toDelete = current->pNextObject;
				}
				current = current->pNextObject;
			}

			if (toDelete == head)
			{
				head = head->pNextObject;
			}
			else
			{
				previous->pNextObject = toDelete->pNextObject;
			}

			T toReturn = toDelete->value;

			delete toDelete;
			toDelete = nullptr;
			--size;

			return toReturn;
		}
	}
	// проверяет, пустой ли стэк
	bool IsEmpty()
	{
		return size == 0;
	}
	// очищает стэк
	void Clear()
	{
		while (size)
		{
			this->Pop();
		}
	}
	void ShowAll()
	{
		if (size < 1)
		{
			std::cout << "there is no elements in stack to show\n";
		}
		PrioritizedObject<T>* toShow = this->head;
		for (size_t i = 0; i < size; ++i)
		{
			std::cout << toShow->value << "\t|\t" << toShow->priority << std::endl;
			toShow = toShow->pNextObject;
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

	priority_stack.Pop();

	return 0;
}