#pragma once
#include "../Engine/Math/Math.h"

class AABBTreeNode {
public:
	Rect2 aabb_;
	//この項が葉で1つのAABBを表す場合そのAABBのid，それ以外の場合(前回分未クリア含む)-1とする
	unsigned int id_;
	AABBTreeNode() :aabb_(-1e9, -1e9, -1e9, -1e9), id_(-1) {};
};

//AABB木を構築する
class AABBTree
{
public:
	//queryと保持する全AABBとの当たり判定を行い，衝突するAABBのインデックスを格納する
	//(インデックスは，構築時渡された配列のもの)
	void TraverseAgainst(Rect2 query,std::vector<unsigned int>& hit_ids);
	//このAABBの配列からAABB木を構築する
	void ConstructAABBTree(const std::vector<Rect2>& nodes);
private:
	//AABBの最大保持個数
	static constexpr unsigned int maxaabb_ = 1024;
	//木の実体(tree_[1]を根，tree_[n]の子はtree_[2*n]とtree_[2*n+1]とする)
	AABBTreeNode tree_[maxaabb_ * 2];
	//2つのAABBの共通範囲の面積
	static inline double GetSharedSurface(const Rect2& a, const Rect2& b)
	{
		double lx = max(a.GetLD()(0), b.GetLD()(0));
		double rx = min(a.GetRU()(0), b.GetRU()(0));
		double dy = max(a.GetLD()(1), b.GetLD()(1));
		double uy = min(a.GetRU()(1), b.GetRU()(1));
		return min(rx - lx, 0.0) * min(uy - dy, 0.0);
	}
	//baseを，baseとtarget両方を含むAABBに変更
	static inline void Merge(Rect2& base, const Rect2& target)
	{
		base.LD() = MatVec::Vector2(min(base.LD()(0), target.GetLD()(0)), min(base.LD()(1), target.GetLD()(1)));
		base.RU() = MatVec::Vector2(max(base.RU()(0), target.GetRU()(0)), max(base.RU()(1), target.GetRU()(1)));
	}
	//aとbが共通部を持つか否か
	static inline bool IsCrossing(const Rect2& a, const Rect2& b)
	{
		return !(
			a.GetLD()(0) > b.GetRU()(0) ||
			a.GetRU()(0) < b.GetLD()(0) ||
			a.GetLD()(1) > b.GetRU()(1) ||
			a.GetRU()(1) < b.GetLD()(1)
			);
	}
	//ConstructAABBTreeのサブ関数
	//tree_[id]の設定が終わった状態で，nodes[left]~nodes[right]を子に振り分け，tree_[id]の子の構築を行う
	void ConstructAABBTree(std::vector<AABBTreeNode>& nodes, unsigned int left,unsigned int right, unsigned int id);
	//queryとtree_[target]部分木全体との当たり判定を行う
	void TraverseAgainst(Rect2 query, unsigned int target, std::vector<unsigned int>& hit_ids);
};

