
#pragma once
#include <iostream>
#include <string>

template <typename T, typename T1>class MultiMap;

template <typename T, typename T1>
std::ostream& operator << (std::ostream& out, const MultiMap<T, T1>&);
class Iterator;

template <typename T, typename T1>
class MultiMap
{
private:
	template <typename T, typename T1>
	class Node
	{
	public:
		std::string color_;
		T key_;
		T1 data_;
		Node* p; //указатель на родителя
		Node* left;
		Node* right;
		friend class Iterator;
		Node(T key, T1 data)
		{
			key_ = key;
			data_ = data;
			p = nullptr;
			left = nullptr;
			right = nullptr;
			color_ = "black";
		}

		Node(T key, T1 data, std::string color, Node* left, Node* right)
		{
			key_ = key;
			data_ = data;
			this->p = p;
			this->left = left;
			this->right = right;
			color_ = color;

		}

	};

	Node<T, T1>* node_;
	int Size;
	Node<T, T1>* T_nill;

	void RightRotated(Node<T, T1>* current);
	void LeftRotated(Node<T, T1>* current);
	void InsertFixup(Node<T, T1>* current);
	void outputTreeCurrentStraight(Node<T, T1>* current);
	void outputTreeCurrentLeft(Node<T, T1>* current) const;
	void outputTreeCurrentRight(Node<T, T1>* current);
	void rbTransplant(Node <T, T1>* u, Node <T, T1>* v);
	void rbDelete(Node<T, T1>* current);
	void rbDeleteFixUp(Node <T, T1>* x);
	void deleteTree(Node<T, T1>* root);


	Node<T, T1>* treeMinimum(Node <T, T1>* current)
	{
		while (current->left == T_nill)
		{
			current = current->left;
		}
		return current;
	}
public:
	MultiMap();
	~MultiMap();
	void Multimap(const MultiMap<T, T1>& tree); //??????
	void Insert(T key, T1 data);
	void outputTreeStraight();
	void outPutTreeLeft() const;
	void outPutTreeRight();
	void correctInfo(T key, T1 data);
	friend std::ostream& operator << <>(std::ostream& out, const MultiMap&);
	T1 operator [](const T key);
	void erase(const T key);
	friend class Iterator;

	class Iterator
	{
	public:
		friend class MultiMap<T, T1>;
		Node<T, T1>* root_;
		static Node<T, T1>* rootNill_;
		Iterator(Node<T, T1>* root) : root_(root) {}
		Iterator()
		{
			root_ = nullptr;
			//rootNill_ = MultiMap<T, T1>::Node<T, T1> T_nill;
		}
		bool operator != (Iterator const& other) const
		{
			return this->root_ != other.root_;
		}
		bool operator == (Iterator const& other) const
		{
			return this->root_ == other.root_;
		}
		Iterator operator = (Node<T, T1> const& tree)
		{
			root_ = tree;
		}
		Node<T, T1> operator * () { return *root_; }
		Iterator& operator++()
		{
			if (root_->right->right != nullptr)
				root_ = left(root_->right);
			else if (root_->right->right == nullptr)
			{
				//root_ = root_->p;
				while (root_->p->left != root_ && root_->p->left != nullptr)
					root_ = root_->p;
				root_ = root_->p;
			}

			else
				root_ = nullptr;
			return *this;

		}
	private:
		Node<T, T1>* right(Node<T, T1>* current)
		{
			Node<T, T1>* x = nullptr;
			while (current->right != nullptr) //Необходимо доходить до ограничителя!!!
			{
				x = current;
				current = current->right;
			}
			return x;
		}
		void current(Node<T, T1>* root)
		{
			if (root->left->left != nullptr)
				current(root->left);
			if (root->right->right != nullptr)
				current(root->right);
		}
		Node<T, T1>* left(Node<T, T1>* current)
		{
			Node<T, T1>* x = nullptr;
			while (current->left != nullptr)
			{
				x = current;
				current = current->left;
			}
			return x;
		}

	};
	Iterator minLeft(Iterator& current)
	{
		while (current.root_->left != T_nill)
			current.root_ = current.root_->left;
		return current;
	}
	Iterator runTree(Iterator current, const T key)
	{
		if (current.root_ != T_nill)
		{
			if (current.root_->key_ < key)
				current = runTree(current.root_->right, key);
			else if (current.root_->key_ > key)
				current = runTree(current.root_->left, key);
			else
				return current;
		}
		else
			return current;
	}
	Iterator leftUbound(Iterator current)
	{
		while (current.root_->right != T_nill)
			current = leftUbound(current.root_->right);
		return current;
	}
	Iterator rightLUbound(Iterator current)
	{
		while (current.root_->left != T_nill)
			current = rightLUbound(current.root_->left);
		return current;

	}
	Iterator begin()
	{
		Iterator x = node_;
		if (x != T_nill)
			x = minLeft(x);
		return x;
	}
	Iterator end()
	{
		return T_nill;
	}
	Iterator ubound(const T key)
	{
		Iterator x = node_;
		x = runTree(x, key);
		if (x.root_->left != T_nill)
			x = leftUbound(x.root_->left);
		else if (x.root_->p->left == x.root_) //если текущий слева и ниже по дереву никого нет, то возвращаем родителя
			x = x.root_->p; //перепроверить!!!
		else                //если он справа находится и большего ключа нет, то возвращаем T_nill
			x = end();
		return x;

	}
	Iterator lbound(const T key)
	{
		Iterator it = node_;
		it = runTree(it, key);
		if (it.root_->right != T_nill)
			it = rightLUbound(it.root_->right);
		else if (it.root_->right == T_nill)
		{
			while (it.root_->p->right != it.root_ && it.root_->p != T_nill) //если текущий не имеет сына справа, то поднимаемся до тех пор, пока не будем справа и возвращаем родителя
			{
				it = it.root_->p;
			}
			it = it.root_->p;
		}
		else
			it = end();
		return it;
	}

	void Swap(MultiMap<T, T1>& tree)
	{
		if (tree.node_ != nullptr && node_ != nullptr)
		{
			Node <T, T1>* tmp_node = node_;
			node_ = tree.node_;
			tree.node_ = tmp_node;
			tmp_node = T_nill;
			T_nill = tree.T_nill;
			tree.T_nill = tmp_node;
		}
	}
	friend std::ostream& operator << (std::ostream& out, const Node<T, T1>& root)
	{
		out << root.data_ << " данные \t" << root.key_ << " ключ \t" << std::endl;
		return out;
	}

};



template <typename T, typename T1> MultiMap<T, T1>::MultiMap()
{
	node_ = nullptr;
	T_nill = nullptr;
	Size = 0;
}

template<typename T, typename T1>
MultiMap<T, T1>::~MultiMap()
{
	deleteTree(node_);
}

template<typename T, typename T1>
void MultiMap<T, T1>::Multimap(const MultiMap<T, T1>& tree)
{
	if (this->node_ == nullptr)
	{

	}
}

template<typename T, typename T1>
void MultiMap<T, T1>::Insert(T key, T1 data)

{
	if (T_nill == nullptr)
		T_nill = new Node<T, T1>(key, data, "black", nullptr, nullptr);

	Node<T, T1>* current = new Node<T, T1>(key, data, "red", nullptr, nullptr);
	if (node_ == nullptr)
	{
		node_ = current;
		node_->p = this->T_nill;
		node_->left = this->T_nill;
		node_->right = this->T_nill;
		current->color_ = "black";
	}
	else
	{
		Node <T, T1>* x = node_;//туда же куда и корень дерева, "вниз" по узлу
		Node <T, T1>* y = nullptr; //пока зануляем (вообще будем смотреть "сверху" узла)

		while (x != nullptr and x != T_nill) //Идем сверху вниз по дереву
		{
			y = x; //перемещаемся
			if (x->key_ < current->key_) //если текущий больше, идем направо, иначе...
				x = x->right;
			else
				x = x->left;
		}
		current->p = y;
		//расставляем указатели относительно y, т.е. сверху на current
		if (y->key_ < current->key_)
			y->right = current;
		else
			y->left = current;

		current->left = T_nill;
		current->right = T_nill;
		current->color_ = "red";
		InsertFixup(current);
	}
	Size++;
}

template<typename T, typename T1>
void MultiMap<T, T1>::outputTreeStraight()
{
	if (node_ != nullptr)
		outputTreeCurrentStraight(node_);
	else
		std::cout << "Пустое дерево!" << std::endl;
}

template<typename T, typename T1>
void MultiMap<T, T1>::outPutTreeLeft() const
{
	if (node_ != nullptr)
		outputTreeCurrentLeft(node_);
	else
		std::cout << "Пустое дерево!" << std::endl;
}

template<typename T, typename T1>
void MultiMap<T, T1>::outPutTreeRight()
{
	if (node_ != nullptr)
		outputTreeCurrentRight(node_);
	else
		std::cout << "Пустое дерево!" << std::endl;
}

template<typename T, typename T1>
void MultiMap<T, T1>::correctInfo(T key, T1 data)
{
	Node<T, T1>* current = node_;
	while (current != T_nill && current->p->key_ != key)
	{
		if (current->key_ == key)
		{
			current->data_ = data;
			current = current->left;
		}
		else if (current->key_ > key)
			current = current->left;
		else
			current = current->right;
	}
}

template<typename T, typename T1>
T1 MultiMap<T, T1>::operator[](const T key)
{
	Node<T, T1>* current = node_;
	while (current != T_nill)
	{
		if (current->key_ == key)
			return current->data_;
		else if (current->key_ > key)
			current = current->left;
		else
			current = current->right;
	}
	//если нет такого ключа необходимо вернуть итератор, обозначающий лист дерева!!!
}

template<typename T, typename T1>
void MultiMap<T, T1>::erase(const T key)
{
	Node<T, T1>* current = node_;
	while (current != nullptr && current != T_nill)
	{
		if (current->key_ == key)
		{
			rbDelete(current);
			current->left = nullptr;
			current->right = nullptr;
			std::cout << "Delete current" << current->key_ << std::endl;
			delete current;
			current = nullptr;
			//current = current->left;
		}
		else if (current->key_ < key)
			current = current->right;
		else
			current = current->left;
	}
	//иначе вернуть иттератор end;
	//current->left = nullptr; //спросить надо ли nullptr слева и справа??????
	//current->right = nullptr;
	//delete current;
	//current = nullptr;
}

template<typename T, typename T1>
void MultiMap<T, T1>::outputTreeCurrentStraight(Node<T, T1>* current)
{
	std::cout << "Ключ: " << current->key_ << " \t" << "Данные: " << current->data_ << "\t" << "Цвет: " << current->color_ << std::endl;
	if (current->left != T_nill)
		outputTreeCurrentStraight(current->left);
	if (current->right != T_nill)
		outputTreeCurrentStraight(current->right);
}

template<typename T, typename T1>
void MultiMap<T, T1>::outputTreeCurrentLeft(Node<T, T1>* current) const
{
	if (current->left != T_nill)
		outputTreeCurrentLeft(current->left);
	std::cout << "Ключ: " << current->key_ << " \t" << "Данные: " << current->data_ << "\t" << "Цвет: " << current->color_ << std::endl;
	if (current->right != T_nill)
		outputTreeCurrentLeft(current->right);
}

template<typename T, typename T1>
void MultiMap<T, T1>::outputTreeCurrentRight(Node<T, T1>* current)
{
	if (current->right != T_nill)
		outputTreeCurrentRight(current->right);
	std::cout << "Ключ: " << current->key_ << " \t" << "Данные: " << current->data_ << "\t" << "Цвет: " << current->color_ << std::endl;
	if (current->left != T_nill)
	{
		outputTreeCurrentRight(current->left);
	}
}

template<typename T, typename T1>
void MultiMap<T, T1>::rbTransplant(Node<T, T1>* u, Node<T, T1>* v)
{
	if (u->p == T_nill)
		node_ = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;

	v->p = u->p;
}

template<typename T, typename T1>
void MultiMap<T, T1>::rbDelete(Node<T, T1>* current)
{
	Node<T, T1>* y = current;
	Node<T, T1>* x = nullptr;
	std::string y_color = y->color_;

	if (current->left == T_nill)
	{
		x = current->right;
		rbTransplant(current, current->right);
	}
	else if (current->right == T_nill)
	{
		x = current->left;
		rbTransplant(current, current->left);
	}
	else
	{
		y = treeMinimum(current->right);
		y_color = y->color_;
		x = y->right;
		if (y->p == current)
			x->p = y;
		else
		{
			rbTransplant(y, y->right);
			y->right = current->right;
			y->right->p = y;
		}
		rbTransplant(current, y);
		y->left = current->left;
		y->left->p = y;
		y->color_ = current->color_;
	}
	if (y_color == "black")
		rbDeleteFixUp(x);

	Size--;
}

template<typename T, typename T1>
void MultiMap<T, T1>::rbDeleteFixUp(Node<T, T1>* x)
{
	Node<T, T1>* w = nullptr;
	while (x != node_ && x->color_ == "black")
	{
		if (x == x->p->left) //если левый ребенок
		{
			w = x->p->right;
			if (w->color_ == "red") //если брат красный
			{
				w->color_ = "black"; //окрашиваем брата в черный
				x->p->color_ = "red"; //отца в красный
				LeftRotated(x->p); //брат становится отцом родителя
				w = x->p->right;
			}
			//случай 1(брат красный с черными детьми)
			if (w->left->color_ == "black" && w->right->color_ == "black") //если у брата черные дети
			{
				w->color_ = "red";
				x = x->p;
			}
			else
			{
				if (w->right->color_ == "black")
				{
					w->left->color_ = "black";
					w->color_ = "red";
					RightRotated(w);
					w = x->p->right;
				}
				w->color_ = x->p->color_;
				x->p->color_ = "black";
				w->right->color_ = "black";
				LeftRotated(x->p);
				x = node_;
			}
		}
		else //x - правый ребенок
		{
			w = x->p->left;
			if (w->color_ == "red") //если брат красный
			{
				w->color_ = "black"; //окрашиваем брата в черный
				x->p->color_ = "red"; //отца в красный
				RightRotated(x->p);
				w = x->p->right;
			}
			if (w->right->color_ == "black" && w->left->color_ == "black") //если у брата черные дети
			{
				w->color_ = "red";
				x = x->p;
			}
			else
			{
				if (w->left->color_ == "black")
				{
					w->right->color_ = "black";
					w->color_ = "red";
					LeftRotated(w);
					w = x->p->left;
				}
				w->color_ = x->p->color_;
				x->p->color_ = "black";
				w->left->color_ = "black";
				RightRotated(x->p);
				x = node_;
			}
		}
	}
	x->color_ = "black";
}

template<typename T, typename T1>
void MultiMap<T, T1>::deleteTree(Node<T, T1>* root)
{
	Node <T, T1>* y = nullptr;
	if (root->left != T_nill)
	{
		deleteTree(root->left);
	}
	else if (root->right != T_nill)
	{
		deleteTree(root->right);
	}
	else
	{
		if (root != node_)
		{
			y = root->p;
			if (root == y->left)
			{
				y->left = T_nill;
			}
			else
			{
				y->right = T_nill;
			}
			root->left = nullptr;
			root->right = nullptr;
			Size--;
			delete root;
			root = nullptr;
			deleteTree(y);
		}
	}
	if (node_ != nullptr)
	{
		node_->left = nullptr;
		node_->right = nullptr;
		delete node_;
		node_ = nullptr;
		delete T_nill;
		T_nill = nullptr;
	}
}

template<typename T, typename T1>
void MultiMap<T, T1>::RightRotated(Node<T, T1>* current)
{
	Node <T, T1>* y = current->left;
	current->left = y->right;
	if (current->left != T_nill)
	{
		current->left->p = current;
	}
	Node <T, T1>* t = y->p->p;
	y->p = t;   //???????
	if (y->p == T_nill)
	{
		node_ = y;
	}
	else if (current == current->p->left)
	{
		current->p->left = y;
	}
	else
	{
		current->p->right = y;
	}
	y->right = current;
	current->p = y;
}

template<typename T, typename T1>
void MultiMap<T, T1>::LeftRotated(Node <T, T1>* current)
{
	Node<T, T1>* y = current->right;
	current->right = y->left;
	if (y->left != T_nill)
	{
		y->left->p = current;
	}
	y->p = current->p;

	if (current->p == T_nill)
	{
		node_ = y;
	}
	else if (current == current->p->left)
	{
		current->p->left = y;
	}
	else
	{
		current->p->right = y;
	}
	y->left = current;
	current->p = y;
}

template<typename T, typename T1>
void MultiMap<T, T1>::InsertFixup(Node<T, T1>* current)
{
	Node<T, T1>* y = nullptr;
	if (current != node_)//если корень, то просто окраш. в ч
	{
		while (current->p->color_ == "red" and current != node_)

		{
			if (current->p == current->p->p->left) //отец левый ребенок
			{
				y = current->p->p->right;

				if (y->color_ == "red")
				{
					current->p->color_ = "black";
					y->color_ = "black";
					current->p->p->color_ = "red";
					current = current->p->p;
				}

				else //когда нет "дяди"
				{
					if (current == current->p->right)
					{
						current = current->p;
						LeftRotated(current);
					}
					current->p->color_ = "black";
					current->p->p->color_ = "red";
					RightRotated(current->p->p);
				}
			}
			else //отец правый ребенок
			{
				y = current->p->p->left;
				if (y->color_ == "red") //дядя красный &&&&&&&&&&&&&&&&&&&&
				{
					current->p->color_ = "black";
					y->color_ = "black";
					current->p->p->color_ = "red";
					current = current->p->p;
				}

				else //нет дяди
				{
					if (current == current->p->left) //текущий узел слева
					{
						current = current->p;
						RightRotated(current);
					}
					current->p->color_ = "black";
					current->p->p->color_ = "red";
					LeftRotated(current->p->p);
				}
			}
		}
		node_->color_ = "black";
	}
	else
		current->color_ = "black";
}


template <typename T, typename T1>
std::ostream& operator  << (std::ostream& out, const MultiMap<T, T1>& tree)
{
	tree.outPutTreeLeft();
	return out;
}



