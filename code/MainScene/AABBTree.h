#pragma once
#include "../Engine/Math/Math.h"

class AABBTreeNode {
public:
	Rect2 aabb_;
	//���̍����t��1��AABB��\���ꍇ����AABB��id�C����ȊO�̏ꍇ(�O�񕪖��N���A�܂�)-1�Ƃ���
	unsigned int id_;
	AABBTreeNode() :aabb_(-1e9, -1e9, -1e9, -1e9), id_(-1) {};
};

//AABB�؂��\�z����
class AABBTree
{
public:
	//query�ƕێ�����SAABB�Ƃ̓����蔻����s���C�Փ˂���AABB�̃C���f�b�N�X���i�[����
	//(�C���f�b�N�X�́C�\�z���n���ꂽ�z��̂���)
	void TraverseAgainst(Rect2 query,std::vector<unsigned int>& hit_ids);
	//����AABB�̔z�񂩂�AABB�؂��\�z����
	void ConstructAABBTree(const std::vector<Rect2>& nodes);
private:
	//AABB�̍ő�ێ���
	static constexpr unsigned int maxaabb_ = 1024;
	//�؂̎���(tree_[1]�����Ctree_[n]�̎q��tree_[2*n]��tree_[2*n+1]�Ƃ���)
	AABBTreeNode tree_[maxaabb_ * 2];
	//2��AABB�̋��ʔ͈̖͂ʐ�
	static inline double GetSharedSurface(const Rect2& a, const Rect2& b)
	{
		double lx = max(a.GetLD()(0), b.GetLD()(0));
		double rx = min(a.GetRU()(0), b.GetRU()(0));
		double dy = max(a.GetLD()(1), b.GetLD()(1));
		double uy = min(a.GetRU()(1), b.GetRU()(1));
		return min(rx - lx, 0.0) * min(uy - dy, 0.0);
	}
	//base���Cbase��target�������܂�AABB�ɕύX
	static inline void Merge(Rect2& base, const Rect2& target)
	{
		base.LD() = MatVec::Vector2(min(base.LD()(0), target.GetLD()(0)), min(base.LD()(1), target.GetLD()(1)));
		base.RU() = MatVec::Vector2(max(base.RU()(0), target.GetRU()(0)), max(base.RU()(1), target.GetRU()(1)));
	}
	//a��b�����ʕ��������ۂ�
	static inline bool IsCrossing(const Rect2& a, const Rect2& b)
	{
		return !(
			a.GetLD()(0) > b.GetRU()(0) ||
			a.GetRU()(0) < b.GetLD()(0) ||
			a.GetLD()(1) > b.GetRU()(1) ||
			a.GetRU()(1) < b.GetLD()(1)
			);
	}
	//ConstructAABBTree�̃T�u�֐�
	//tree_[id]�̐ݒ肪�I�������ԂŁCnodes[left]~nodes[right]���q�ɐU�蕪���Ctree_[id]�̎q�̍\�z���s��
	void ConstructAABBTree(std::vector<AABBTreeNode>& nodes, unsigned int left,unsigned int right, unsigned int id);
	//query��tree_[target]�����ؑS�̂Ƃ̓����蔻����s��
	void TraverseAgainst(Rect2 query, unsigned int target, std::vector<unsigned int>& hit_ids);
};

