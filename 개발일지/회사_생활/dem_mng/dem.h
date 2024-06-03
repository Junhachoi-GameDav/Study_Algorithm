#pragma once
// std
#include <filesystem>
#include <array>
#include <string>
#include <locale>
#include <system_error>

//namespace std
//{
//	namespace filesystem
//	{
//		class path;
//	}
//}
// OpenCV
#include <opencv2/core.hpp>

//#include "point_cloud.h"
//#include "dem_manager.h"

//.img Ȯ���� dem�� v2
class demv2
{
	// DEM �������� �»�� ��ġ, �Ϲ������δ� �̹����� �����¿�� DEM�� �ϳ������� ���߱� ������ ������ǥ������ �Ϲ������� (min x, max y) �̴�.
	cv::Point2d left_top;

	// ������ǥ x, y�� ��ȭ��(�ȼ�) �� DEM x, y�� ������ǥ ��ȭ��. ������ DEM�� �����ϴ� ��ǥ�迡 �޷��ִ�. ���� ����.
	// left-top�� �Ϲ������� (min x, max y)�� delta�� (+, -)�� ��찡 ����.
	cv::Point2d delta;

	// �� x, y ������ z���� ���̰� ��� Mat
	// dem�� �̹����̹Ƿ� ����ȭ �Ǿ��ִ�. subpixel�� ���̴� �ּ���(bilinear) �����ؼ� ����Ѵ�.
	// x, y ��ġ�� ������ ���� ����Ѵ�.
	// x = left_top.x + m(horizontal pixel offset) * delta.x
	// y = left_top.y + n(vertical pixel offset) * delta.y
	// z(x, y) = dem_matrix(m, n)
	mutable cv::Mat dem_matrix;

	// dem_matrix�� ũ��, ������ ���� �ִ� ������ �����ϴ� DEM�� �������鼭 �޸� �뷮�� �˳�ġ �ʾƼ�
	// dem_matrix�� ��� ������ ������ �˻��� ���� �ֵ��� �ϱ� ����.
	cv::Size dem_size;

	// �޸� ������ ���� �ӽ÷� ������ �� �� ������ ã�� ���� ���(unload()/reload() �Լ� ����)
	// dem_matrix.release() �Ͽ� �޸𸮸� ���̵� ������ �˻��� ���� �ֵ��� ������� ������ ���� �ִ´�.
	std::filesystem::path abs_path;

	// internal ctors
	demv2() = default;
	//demv2(const double& dx, const double& dy, const cv::Mat& dem_mat);

public:
	// public ctors
	demv2(const std::filesystem::path& dem_file);

	// copyable
	demv2(const demv2&) = default;
	demv2& operator=(const demv2&) = default;

	// movable
	demv2(demv2&&) = default;
	demv2& operator=(demv2&&) = default;

	// default dtor
	~demv2() = default;

	// ���� �� �ش� ��ǥ ���� ����
	// ��Ȯ�ϰ� �� ���� ������ DEM�� �����ϴ� ���� ���� �ִ��� �Ǵ��Ѵ�.
	bool contains(const double& x, const double& y) const;

	// �ش� ��ǥ ���� ã��
	// ��κ� �ش� ��ǥ�� ��Ȯ�ϰ� ��� ���� �ʱ� ������ ��Ȯ�� ���̰��� ����.
	// ��� ������ 4�� ���� ã�� �ּ��� ����(bilinear interpolation) �Ѵ�.
	// ���� ���� ������(contains(x, y) == false) nan�� �����Ѵ�.
	double find_ground_height(const double& x, const double& y) const;

	// �޸� ������ ���� �뷮�� ��������� ū dem_matrix�� ��ε�/���ε� �ϴ� �Լ�
	// �޸� ��뷮�� ��Ը� File IO�� ���� ���� �϶� �� Ÿ������ ã�� ������ �ø��� ���� �� 
	void unload() const;
	void reload() const;

	friend class dem_manager;
};
