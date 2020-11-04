#include <iostream>
#include <string>
/*
	   ДОМАШНЕЕ ЗАДАНИЕ:
	   Задание 1: Реализуйте шаблонный класс (FIFO) priority_queue
	   Методы очереди:
	   + front() возвращает ссылку на первый элемент в очереди
	   + back() возвращает ссылку на последний элемент в очереди
	   + pop() извлекает первый элемент из очереди
	   + push(element) добавляет элемент в очередь
	   + size() возвращает количество элементов в очереди
	   + swap(other_queue) обменивает содержимым две очереди
	   + empty() возвращает true если очередь пустая и false в противном случае
	   + конструкторы/операторы копирования/перемещения
	   + распечатайте содержимое очереди за пределами класса queue
	   + Реализация данного класса должна быть такой же как и реализация
	   очереди из первого задания, только в данном случае
	   + при создании объекта у нас должна быть возможность указать тип функтора,
	   на основе которого будет определяться расположение элементов в очереди
	   + Реализуйте два функтора которые будут определять расположение
		 элементов в очереди (от малого к большему и наоборот)


	   Dopolnitelno
	   + add circular_buffer
   */

struct Down {
	template<typename T>
	bool operator() (const T left, const T right) {
		return left < right;
	}
};

struct Up {
	template<typename T>
	bool operator() (const T left, const T right) {
		return left > right;
	}
};

template<typename T, typename  Tsort>
class Priority_queue
{
public:
	Priority_queue(const int size)
	{
		m_size = size;
		m_arr = new T[m_size];
	}

	~Priority_queue()
	{
		delete[] m_arr;
	}

	T& front()
	{
		return m_arr[0];
	}

	void pop()
	{
		T* tmp = new T[m_size];
		for (size_t i = 1, b = 0; i < m_index; b++, i++) {
			tmp[b] = m_arr[i];
		}
		delete[] m_arr;
		m_arr = tmp;
		m_index--;
	}


	T& back()
	{
		return m_arr[m_index - 1];
	}

	void push(const T& element)
	{
		Tsort sort;
		if (m_index < m_size) {
			m_arr[m_index++] = element;
		}
		else {
			circular_buffer();
			m_arr[m_index - 1] = element;
		}

		for (size_t i = 0; i < m_index; i++) {
			for (size_t j = i + 1; j < m_index; j++) {
				if (sort(m_arr[i], m_arr[j])) {
					std::swap(m_arr[i], m_arr[j]);
				}
			}
		}

	}

	int size()const
	{
		return m_index;
	}

	bool empty()const
	{
		return m_index == 0;
	}

	Priority_queue(const Priority_queue& other)
	{
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = new T[m_size];

		for (size_t i = 0; i < m_index; i++)
			m_arr[i] = other.m_arr[i];
	}

	void swap(Priority_queue& other)
	{
		Priority_queue tmp = std::move(other);
		other = std::move(*this);
		*this = std::move(tmp);
	}

	Priority_queue(Priority_queue&& other)
	{
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = other.m_arr;
		other.m_arr = nullptr;
	}

	Priority_queue& operator=(const Priority_queue& other)
	{
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = new T[m_size];

		for (size_t i = 0; i < m_index; i++)
			m_arr[i] = other.m_arr[i];

		return *this;
	}

	Priority_queue& operator=(Priority_queue&& other)
	{
		m_index = other.m_index;
		m_size = other.m_size;
		m_arr = other.m_arr;
		other.m_arr = nullptr;

		return *this;
	}

private:

	 template<typename T, typename  Tsort>
	friend std::ostream& operator<<(std::ostream& os, Priority_queue<typename T, typename  Tsort>& n)
	{
		for (size_t i = 0; i < n.m_index; i++) {
			os << n.m_arr[i] << ' ';
		}
		return os;
	}

	void circular_buffer() {
		for (size_t i = 1, b = 0; i < m_size; b++, i++) {
			m_arr[b] = m_arr[i];
		}
	}

	size_t m_size;
	size_t m_index = 0;
	T* m_arr = nullptr;
};





int main()
{
	Priority_queue<int, Up> arr(3);

	arr.push(1);
	arr.push(2);
	arr.push(3);
	arr.push(4);
	arr.push(1);
	arr.push(5);

	std::cout << arr;
}