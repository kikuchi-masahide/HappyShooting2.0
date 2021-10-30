#include "stdafx.h"
#include "AABBTree.h"

void AABBTree::TraverseAgainst(Rect2 query, std::vector<unsigned int>& hit_ids)
{
	TraverseAgainst(query, 1, hit_ids);
}

void AABBTree::ConstructAABBTree(std::vector<Rect2>& nodes)
{
	//AABBの数が0ならば，どっか遠いところにAABBを設定しておく
	if (nodes.size() == 0)
	{
		tree_[1].aabb_ = Rect2(-1e9, -1e9, -1e9, -1e9);
		tree_[1].id_ = -1;
	}
	//1つならばそれをそのまま根とする
	else if (nodes.size() == 1)
	{
		tree_[1].aabb_ = nodes[0];
		tree_[1].id_ = 0;
	}
	//2個以上ならば再帰
	else {
		//勝手にソートしてもいい配列をコピー
		std::vector<AABBTreeNode> copy;
		copy.resize(nodes.size());
		for (unsigned int n = 0; n < nodes.size(); n++)
		{
			copy[n].aabb_ = nodes[n];
			copy[n].id_ = n;
		}
		//根のAABBはnodes全部の融合
		tree_[1].aabb_ = nodes[0];
		for (unsigned int n = 1; n < nodes.size(); n++)
		{
			Merge(tree_[1].aabb_, nodes[n]);
		}
		tree_[1].id_ = -1;
		ConstructAABBTree(copy, 0, copy.size() - 1, 1);
	}
}

void AABBTree::ConstructAABBTree(std::vector<AABBTreeNode>& nodes, unsigned int left, unsigned int right, unsigned int id)
{
	unsigned int N = right - left + 1;
	//TODO:ここの振り分け方の最適化
	//以下のλ式でソートを行う:
	//0-右x昇順
	//1-左x昇順
	//2-上y昇順
	//3-下y昇順
	//それぞれのソートで，最初のN/2個であるA群を子2*idに，最後のN-N/2個であるB群を子2*id+1に振り分けAABBを作る．
	//2つの子の共通部がもっとも小さくなる分け方を採用する．
	//A，B群の数
	unsigned int Na = N / 2;
	unsigned int Nb = N - Na;
	static std::function<bool(const AABBTreeNode&,const AABBTreeNode&)> lambdas[4];
	lambdas[0] = [](const AABBTreeNode& left, const AABBTreeNode& right)
	{
		return left.aabb_.GetRU()(0) < right.aabb_.GetRU()(0);
	};
	lambdas[1] = [](const AABBTreeNode& left, const AABBTreeNode& right)
	{
		return left.aabb_.GetLD()(0) < right.aabb_.GetLD()(0);
	};
	lambdas[2] = [](const AABBTreeNode& left, const AABBTreeNode& right)
	{
		return left.aabb_.GetRU()(1) < right.aabb_.GetRU()(1);
	};
	lambdas[3] = [](const AABBTreeNode& left, const AABBTreeNode& right)
	{
		return left.aabb_.GetLD()(1) < right.aabb_.GetLD()(1);
	};
	//共通部最小となったlambdas
	unsigned int min_lambda = 4;
	//その面積
	double min_lambda_a = 1e9;
	for (unsigned int l = 0; l < 4; l++)
	{
		std::sort(nodes.begin() + left, nodes.begin() + right + 1, lambdas[l]);
		//tree_[2*id].aabb_とtree_[2*id].aabb_を仮変更する
		tree_[2 * id].aabb_ = nodes[left].aabb_;
		for (int n = left+1; n < left + Na; n++)
		{
			Merge(tree_[2 * id].aabb_, nodes[n].aabb_);
		}
		tree_[2 * id + 1].aabb_ = nodes[left + Na].aabb_;
		for (int n = left + Na+1; n <= right; n++)
		{
			Merge(tree_[2 * id + 1].aabb_, nodes[n].aabb_);
		}
		double shared_a = GetSharedSurface(nodes[2 * id].aabb_, nodes[2 * id + 1].aabb_);
		if (shared_a < min_lambda_a)
		{
			min_lambda = l;
			min_lambda_a = shared_a;
		}
	}
	//最終的なソートと子の設定
	std::sort(nodes.begin() + left, nodes.begin() + right + 1, lambdas[min_lambda]);
	tree_[2 * id].aabb_ = nodes[left].aabb_;
	for (int n = left + 1; n < left + Na; n++)
	{
		Merge(tree_[2 * id].aabb_, nodes[n].aabb_);
	}
	if (Na != 1) {
		tree_[2 * id].id_ = -1;
		ConstructAABBTree(nodes, left, left + Na - 1, 2 * id);
	}
	else {
		tree_[2 * id].id_ = nodes[left].id_;
	}
	tree_[2 * id + 1].aabb_ = nodes[left + Na].aabb_;
	for (int n = left + Na + 1; n <= right; n++)
	{
		Merge(tree_[2 * id + 1].aabb_, nodes[n].aabb_);
	}
	if (Nb != -1)
	{
		tree_[2 * id + 1].id_ = -1;
		ConstructAABBTree(nodes, left + Na, right, 2 * id + 1);
	}
	else {
		tree_[2 * id + 1].id_ = nodes[left + Na].id_;
	}
}

void AABBTree::TraverseAgainst(Rect2 query, unsigned int target, std::vector<unsigned int>& hit_ids)
{
	if (IsCrossing(query, tree_[target].aabb_))
	{
		if (tree_[target].id_ != -1)
		{
			hit_ids.push_back(tree_[target].id_);
		}
		else {
			TraverseAgainst(query, 2 * target, hit_ids);
			TraverseAgainst(query, 2 * target + 1, hit_ids);
		}
	}
}
