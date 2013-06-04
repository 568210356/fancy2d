////////////////////////////////////////////////////////////////////////////////
/// @file  fcyMath.h
/// @brief 数学库，描述数学相关结构
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyType.h"

#include <cmath>

#define FCYMAX(a,b) (((a)>(b))?(a):(b))
#define FCYMIN(a,b) (((a)<(b))?(a):(b))

/// @addtogroup fancy数学库
/// @brief 提供数学运算支持
/// @note 若无特殊说明，角度单位均为弧度
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief 2D向量
////////////////////////////////////////////////////////////////////////////////
class fcyVec2
{
public:
	fFloat x; ///< @brief x坐标
	fFloat y; ///< @brief y坐标
public: // 构造函数
	fcyVec2()
		: x(0.f), y(0.f) {}
	/// @brief     构造函数
	/// @param[in] X x坐标
	/// @param[in] Y y坐标
	fcyVec2(fFloat X, fFloat Y)
		: x(X), y(Y) {}
	/// @brief     构造函数，从data[0]~data[1]取出浮点值
	/// @warning   不安全的函数
	/// @param[in] data 浮点数组指针
	fcyVec2(fFloat *data)
		: x(data[0]), y(data[1]) {}
public: // 运算符重载
	/// @brief 2D向量相加
	fcyVec2 operator+(const fcyVec2& right)const
	{
		return fcyVec2(x + right.x, y + right.y);
	};
	/// @brief 2D向量自加
	fcyVec2& operator+=(const fcyVec2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	};
	/// @brief 2D向量相减
	fcyVec2 operator-(const fcyVec2& right)const
	{
		return fcyVec2(x - right.x, y - right.y);
	};
	/// @brief 2D向量自减
	fcyVec2& operator-=(const fcyVec2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	};
	/// @brief 2D向量数乘
	fcyVec2 operator*(fFloat right)const
	{
		return fcyVec2(x * right, y * right);
	};
	/// @brief 2D向量自数乘
	fcyVec2& operator*=(fFloat right)
	{
		x = x * right;
		y = y * right;
		return *this;
	};
	/// @brief 2D向量点积
	fFloat operator*(const fcyVec2& right)const
	{
		return x * right.x + y * right.y;
	}
	/// @brief 取反
	fcyVec2 operator-()const
	{
		return fcyVec2(-x, -y);
	};
public: // 函数
	// 设置
	/// @brief 设置新值
	void Set(fFloat X,fFloat Y)
	{
		x = X; y = Y;
	}
	/// @brief 平面叉积
	fFloat Cross(const fcyVec2& right)const
	{
		return  x * right.y - right.x * y;
	};
	/// @brief 规范化向量
	void Normalize()
	{
		fFloat mode = sqrt( x * x +  y * y );
		if(mode != 0)
		{
			x /= mode;
			y /= mode;
		}
	};
	/// @brief 返回规范化向量
	fcyVec2 GetNormalize()const
	{
		fFloat mode=sqrt( x *  x +  y *  y);
		if(mode != 0)
			return fcyVec2(x / mode, y / mode);
		else
			return fcyVec2();
	};
	/// @brief 求模
	fFloat Length()const
	{
		return sqrt( x*x + y*y );
	}
	/// @brief 求模的平方
	fFloat Length2()const
	{
		return ( x*x + y*y );
	}
	/// @brief     逆时针旋转
	/// @param[in] angle 旋转角度
	void Rotation(fFloat angle)
	{
		fFloat s = sin(angle),
		       c = cos(angle);
		fFloat tx = x*c - y*s,
		       ty = x*s + y*c;
		x = tx;
		y = ty;
	}
	/// @brief     逆时针旋转
	/// @note      用于批量旋转，减少三角函数运算
	/// @param[in] s Sin值(=sin(angle))
	/// @param[in] c Cos值(=cos(angle))
	void RotationSC(fFloat s, fFloat c)
	{
		fFloat tx = x*c - y*s,
			ty = x*s + y*c;
		x = tx; y = ty;
	}
	/// @brief 计算与x轴的夹角
	fFloat CalcuAngle()
	{
		return atan2(y,x);
	}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 3D向量
////////////////////////////////////////////////////////////////////////////////
class fcyVec3
{
public:
	fFloat x; ///< @brief x坐标
	fFloat y; ///< @brief y坐标
	fFloat z; ///< @brief z坐标
public: // 构造函数
	fcyVec3()
		: x(0.f), y(0.f), z(0.f) {}
	/// @brief     构造函数
	/// @param[in] X x坐标
	/// @param[in] Y y坐标
	/// @param[in] Z z坐标
	fcyVec3(fFloat X, fFloat Y, fFloat Z)
		: x(X), y(Y), z(Z) {}
	/// @brief     构造函数，从data[0]~data[2]取出浮点值
	/// @warning   不安全的函数
	/// @param[in] data 浮点数组指针
	fcyVec3(fFloat *data)
		: x(data[0]), y(data[1]), z(data[2]) {}
public: // 运算符重载
	/// @brief 3D向量相加
	fcyVec3 operator+(const fcyVec3& right)const
	{
		return fcyVec3(
			x + right.x,
			y + right.y,
			z + right.z
			);
	};
	/// @brief 3D向量自加
	fcyVec3& operator+=(const fcyVec3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	};
	/// @brief 3D向量相减
	fcyVec3 operator-(const fcyVec3& right)const
	{
		return fcyVec3(
			x - right.x,
			y - right.y, 
			z - right.z
			);
	};
	/// @brief 3D向量自减
	fcyVec3& operator-=(const fcyVec3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	};
	/// @brief 3D向量数乘
	fcyVec3 operator*(fFloat right)const
	{
		return fcyVec3(
			x * right,
			y * right,
			z * right
			);
	};
	/// @brief 3D向量自数乘
	fcyVec3& operator*=(fFloat right)
	{
		x = x * right;
		y = y * right;
		z = z * right;
		return *this;
	};
	/// @brief 3D向量点积
	fFloat operator*(const fcyVec3& right)const
	{
		return x * right.x + y * right.y + z * right.z;
	};
	/// @brief 取反
	fcyVec3 operator-()const
	{
		return fcyVec3(-x, -y, -z);
	};
public: // 函数
	// 设置
	/// @brief 设值新值
	void Set(fFloat X, fFloat Y, fFloat Z)
	{
		x = X; y = Y; z = Z;
	}
	/// @brief 向量叉积
	fcyVec3 Cross(const fcyVec3& right)const
	{
		return fcyVec3(
			y*right.z -  z*right.y,
			z*right.x -  x*right.z,
			x*right.y -  y*right.x);
	};
	/// @brief 规范化向量
	void Normalize()
	{
		fFloat mode = sqrt( x*x +  y*y +  z*z );
		if(mode != 0)
		{
			x/=mode;
			y/=mode;
			z/=mode;
		}
	};
	/// @brief 返回规范化向量
	fcyVec3 GetNormalize()const
	{
		fFloat mode = sqrt( x*x + y*y + z*z );
		if(mode != 0)
			return fcyVec3( x / mode, y / mode, z / mode);
		else
			return fcyVec3();
	};
	/// @brief 取模
	fFloat Length()const
	{
		return sqrt( x*x + y*y + z*z );
	};
	/// @brief 取模的平方
	fFloat Length2()const
	{
		return x*x + y*y + z*z;
	}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 4D向量
////////////////////////////////////////////////////////////////////////////////
class fcyVec4
{
public:
	fFloat x; ///< @brief x坐标
	fFloat y; ///< @brief y坐标
	fFloat z; ///< @brief z坐标
	fFloat w; ///< @brief w坐标
public: // 构造函数
	fcyVec4()
		: x(0.f), y(0.f), z(0.f), w(0.f) 
	{
		this->w = 10;
	}
	/// @brief     构造函数
	/// @param[in] X x坐标
	/// @param[in] Y y坐标
	/// @param[in] Z z坐标
	/// @param[in] W w坐标
	fcyVec4(fFloat X, fFloat Y, fFloat Z, fFloat W)
		: x(X), y(Y), z(Z), w(W) {}
	/// @brief     构造函数，从data[0]~data[3]取出浮点值
	/// @warning   不安全的函数
	/// @param[in] data 浮点数组指针
	fcyVec4(fFloat *data)
		: x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}
public: // 运算符重载
	/// @brief 4D向量相加
	fcyVec4 operator+(const fcyVec4& right)const
	{
		return fcyVec4(
			x + right.x,
			y + right.y,
			z + right.z,
			w + right.w
			);
	};
	/// @brief 4D向量自加
	fcyVec4& operator+=(const fcyVec4& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		w += right.w;
		return *this;
	};
	/// @brief 4D向量相减
	fcyVec4 operator-(const fcyVec4& right)const
	{
		return fcyVec4(
			x - right.x,
			y - right.y, 
			z - right.z,
			w - right.w
			);
	};
	/// @brief 4D向量自减
	fcyVec4& operator-=(const fcyVec4& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		w -= right.w;
		return *this;
	};
	/// @brief 4D向量数乘
	fcyVec4 operator*(fFloat right)const
	{
		return fcyVec4(
			x * right,
			y * right,
			z * right,
			w * right
			);
	};
	/// @brief 4D向量自数乘
	fcyVec4& operator*=(fFloat right)
	{
		x = x * right;
		y = y * right;
		z = z * right;
		w = w * right;
		return *this;
	};
	/// @brief 取反
	fcyVec4 operator-()const
	{
		return fcyVec4(-x, -y, -z, -w);
	};
public: // 函数
	/// @brief 设值新值
	void Set(fFloat X, fFloat Y, fFloat Z)
	{
		x = X; y = Y; z = Z;
	}
	/// @brief 设值新值
	void Set(fFloat X, fFloat Y, fFloat Z, fFloat W)
	{
		x = X; y = Y; z = Z; w = W;
	}
	/// @brief 规范化向量
	void Normalize()
	{
		fFloat mode = sqrt( x*x +  y*y +  z*z + w*w );
		if(mode != 0)
		{
			x/=mode;
			y/=mode;
			z/=mode;
			w/=mode;
		}
	};
	/// @brief 返回规范化向量
	fcyVec4 GetNormalize()const
	{
		fFloat mode = sqrt( x*x + y*y + z*z + w*w );
		if(mode != 0)
			return fcyVec4( x / mode, y / mode, z / mode, w / mode );
		else
			return fcyVec4();
	};
	/// @brief 取模
	fFloat Length()const
	{
		return sqrt( x*x + y*y + z*z + w*w );
	};
	/// @brief 取模的平方
	fFloat Length2()const
	{
		return x*x + y*y + z*z + w*w;
	}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 4x4矩阵
/// @note  行式矩阵
////////////////////////////////////////////////////////////////////////////////
class fcyMatrix4
{
public:
	union
	{
		struct
		{
			fFloat _11, _12, _13, _14;
			fFloat _21, _22, _23, _24;
			fFloat _31, _32, _33, _34;
			fFloat _41, _42, _43, _44;
		};
		fFloat m[4][4];  /// @brief 矩阵数据域
	};
public:
	/// @brief 初始化为单位矩阵
	fcyMatrix4()
	{
		_11=1.f;  _12=0.f;  _13=0.f;  _14=0.f;
		_21=0.f;  _22=1.f;  _23=0.f;  _24=0.f;
		_31=0.f;  _32=0.f;  _33=1.f;  _34=0.f;
		_41=0.f;  _42=0.f;  _43=0.f;  _44=1.f;
	};
	/// @brief 使用自定义初值初始化矩阵
	fcyMatrix4(fFloat m11,fFloat m12,fFloat m13,fFloat m14,
		fFloat m21,fFloat m22,fFloat m23,fFloat m24,
		fFloat m31,fFloat m32,fFloat m33,fFloat m34,
		fFloat m41,fFloat m42,fFloat m43,fFloat m44)
	{
		_11=m11;  _12=m12;  _13=m13;  _14=m14;
		_21=m21;  _22=m22;  _23=m23;  _24=m24;
		_31=m31;  _32=m32;  _33=m33;  _34=m34;
		_41=m41;  _42=m42;  _43=m43;  _44=m44;
	};
public:
	/// @brief 设置新值
	void Set(fFloat m11,fFloat m12,fFloat m13,fFloat m14,
		fFloat m21,fFloat m22,fFloat m23,fFloat m24,
		fFloat m31,fFloat m32,fFloat m33,fFloat m34,
		fFloat m41,fFloat m42,fFloat m43,fFloat m44)
	{
		_11=m11;  _12=m12;  _13=m13;  _14=m14;
		_21=m21;  _22=m22;  _23=m23;  _24=m24;
		_31=m31;  _32=m32;  _33=m33;  _34=m34;
		_41=m41;  _42=m42;  _43=m43;  _44=m44;
	};
public:
	/// @brief 矩阵相加
	fcyMatrix4 operator+(const fcyMatrix4& right)const
	{
		return fcyMatrix4(
			_11 + right._11, _12 + right._12, _13 + right._13, _14 + right._14,
			_21 + right._21, _22 + right._22, _23 + right._23, _24 + right._24,
			_31 + right._31, _32 + right._32, _33 + right._33, _34 + right._34,
			_41 + right._41, _42 + right._42, _43 + right._43, _44 + right._44
			);
	};
	/// @brief 矩阵自加
	fcyMatrix4& operator+=(const fcyMatrix4& right)
	{
		_11 += right._11; _12 += right._12; _13 += right._13; _14 += right._14;
		_21 += right._21; _22 += right._22; _23 += right._23; _24 += right._24;
		_31 += right._31; _32 += right._32; _33 += right._33; _34 += right._34;
		_41 += right._41; _42 += right._42; _43 += right._43; _44 += right._44;

		return *this;
	};
	/// @brief 矩阵相减
	fcyMatrix4 operator-(const fcyMatrix4& right)const
	{
		return fcyMatrix4(
			_11 - right._11, _12 - right._12, _13 - right._13, _14 - right._14,
			_21 - right._21, _22 - right._22, _23 - right._23, _24 - right._24,
			_31 - right._31, _32 - right._32, _33 - right._33, _34 - right._34,
			_41 - right._41, _42 - right._42, _43 - right._43, _44 - right._44
			);
	};
	/// @brief 矩阵自减
	fcyMatrix4& operator-=(const fcyMatrix4& right)
	{
		_11 -= right._11; _12 -= right._12; _13 -= right._13; _14 -= right._14;
		_21 -= right._21; _22 -= right._22; _23 -= right._23; _24 -= right._24;
		_31 -= right._31; _32 -= right._32; _33 -= right._33; _34 -= right._34;
		_41 -= right._41; _42 -= right._42; _43 -= right._43; _44 -= right._44;

		return *this;
	};
	/// @brief 矩阵相乘
	fcyMatrix4 operator*(const fcyMatrix4& right)const
	{
		return fcyMatrix4(
			_11 * right._11 + _12 * right._21 + _13 * right._31 + _14 * right._41,
			_11 * right._12 + _12 * right._22 + _13 * right._32 + _14 * right._42,
			_11 * right._13 + _12 * right._23 + _13 * right._33 + _14 * right._43,
			_11 * right._14 + _12 * right._24 + _13 * right._34 + _14 * right._44,

			_21 * right._11 + _22 * right._21 + _23 * right._31 + _24 * right._41,
			_21 * right._12 + _22 * right._22 + _23 * right._32 + _24 * right._42,
			_21 * right._13 + _22 * right._23 + _23 * right._33 + _24 * right._43,
			_21 * right._14 + _22 * right._24 + _23 * right._34 + _24 * right._44,

			_31 * right._11 + _32 * right._21 + _33 * right._31 + _34 * right._41,
			_31 * right._12 + _32 * right._22 + _33 * right._32 + _34 * right._42,
			_31 * right._13 + _32 * right._23 + _33 * right._33 + _34 * right._43,
			_31 * right._14 + _32 * right._24 + _33 * right._34 + _34 * right._44,

			_41 * right._11 + _42 * right._21 + _43 * right._31 + _44 * right._41,
			_41 * right._12 + _42 * right._22 + _43 * right._32 + _44 * right._42,
			_41 * right._13 + _42 * right._23 + _43 * right._33 + _44 * right._43,
			_41 * right._14 + _42 * right._24 + _43 * right._34 + _44 * right._44
			);
	};
	/// @brief 矩阵数乘
	fcyMatrix4 operator*(const fFloat& right)const
	{
		return fcyMatrix4(_11 * right,_12 * right,_13 * right,_14 * right,
			_21 * right,_22 * right,_23 * right,_24 * right,
			_31 * right,_32 * right,_33 * right,_34 * right,
			_41 * right,_42 * right,_43 * right,_44 * right );
	};
	/// @brief 矩阵自乘
	fcyMatrix4& operator*=(const fcyMatrix4& right)
	{
		_11 = _11 * right._11 + _12 * right._21 + _13 * right._31 + _14 * right._41;
		_12 = _11 * right._12 + _12 * right._22 + _13 * right._32 + _14 * right._42;
		_13 = _11 * right._13 + _12 * right._23 + _13 * right._33 + _14 * right._43;
		_14 = _11 * right._14 + _12 * right._24 + _13 * right._34 + _14 * right._44;

		_21 = _21 * right._11 + _22 * right._21 + _23 * right._31 + _24 * right._41;
		_22 = _21 * right._12 + _22 * right._22 + _23 * right._32 + _24 * right._42;
		_23 = _21 * right._13 + _22 * right._23 + _23 * right._33 + _24 * right._43;
		_24 = _21 * right._14 + _22 * right._24 + _23 * right._34 + _24 * right._44;

		_31 = _31 * right._11 + _32 * right._21 + _33 * right._31 + _34 * right._41;
		_32 = _31 * right._12 + _32 * right._22 + _33 * right._32 + _34 * right._42;
		_33 = _31 * right._13 + _32 * right._23 + _33 * right._33 + _34 * right._43;
		_34 = _31 * right._14 + _32 * right._24 + _33 * right._34 + _34 * right._44;

		_41 = _41 * right._11 + _42 * right._21 + _43 * right._31 + _44 * right._41;
		_42 = _41 * right._12 + _42 * right._22 + _43 * right._32 + _44 * right._42;
		_43 = _41 * right._13 + _42 * right._23 + _43 * right._33 + _44 * right._43;
		_44 = _41 * right._14 + _42 * right._24 + _43 * right._34 + _44 * right._44;

		return *this;
	};
public:
	/// @brief   快速求逆
	/// @note    对特定的矩阵进行快速求逆操作
	/// @warning 仅当矩阵左上角3*3旋转部分的3个轴向都为单位向量并且两两垂直时可用此法
	void FastInvert()
	{
		/* 
		方法：
			左上角3*3 = 原左上角3*3 转置
			左下角1*3 = 原左下角1*3 正负相反，乘于左上角3*3（转置后）
			剩下不变
		*/
		Set(
			_11, _21, _31, 0.f,
			_12, _22, _32, 0.f,
			_13, _23, _33, 0.f,
			-_41*_11-_42*_12-_43*_13,
			-_41*_21-_42*_22-_43*_23,
			- _41*_31-_42*_32-_43*_33,
			1.f
			);
	};
	/// @brief 转置
	void Transpose()
	{
		Set(
			_11,_21,_31,_41,
			_12,_22,_32,_42,
			_13,_23,_33,_43,
			_14,_24,_34,_44
			);
	};
public:
	/// @brief 返回单位矩阵
	static fcyMatrix4 GetIdentity()
	{
		return fcyMatrix4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief 返回左右手系交换矩阵
	static fcyMatrix4 GetSwaper()
	{
		return fcyMatrix4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     返回平移矩阵
	/// @param[in] vec 平移量
	static fcyMatrix4 GetTranslateMatrix(const fcyVec3& vec)
	{
		return fcyMatrix4(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			vec.x, vec.y, vec.z, 1.f
			);
	};
	/// @brief     返回缩放矩阵
	/// @param[in] value 统一缩放量
	static fcyMatrix4 GetScaleMatrix(const fFloat value)
	{
		return fcyMatrix4(
			value, 0.f, 0.f, 0.f,
			0.f, value, 0.f, 0.f,
			0.f, 0.f, value, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     返回缩放矩阵
	/// @param[in] vec 缩放量
	static fcyMatrix4 GetScaleMatrix(const fcyVec3& vec)
	{
		return fcyMatrix4(
			vec.x, 0.f, 0.f, 0.f,
			0.f, vec.y, 0.f, 0.f,
			0.f, 0.f, vec.z, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	}
	/// @brief     返回绕X轴旋转矩阵
	/// @param[in] angle 旋转角度
	static fcyMatrix4 GetRotateX(const fFloat angle)
	{
		fFloat angle_sin = sin(angle),
			angle_cos = cos(angle);

		return fcyMatrix4(
			1.f, 0.f, 0.f, 0.f,
			0.f, angle_cos, angle_sin, 0.f,
			0.f, -angle_sin, angle_cos, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     返回绕Y轴旋转矩阵
	/// @param[in] angle 旋转角度
	static fcyMatrix4 GetRotateY(const fFloat angle)
	{
		fFloat angle_sin = sin(angle),
			angle_cos = cos(angle);

		return fcyMatrix4(
			angle_cos, 0.f, -angle_sin, 0.f,
			0.f, 1.f, 0.f, 0.f,
			angle_sin, 0.f, angle_cos, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     返回绕Z轴旋转矩阵
	/// @param[in] angle 旋转角度
	static fcyMatrix4 GetRotateZ(const fFloat angle)
	{
		fFloat angle_sin = sin(angle),
			angle_cos = cos(angle);

		return fcyMatrix4(
			angle_cos, angle_sin, 0.f, 0.f,
			-angle_sin, angle_cos, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     返回绕XYZ三轴旋转矩阵
	/// @param[in] yaw   横倾是绕 y 轴旋转的角度
	/// @param[in] pitch 纵倾是绕 x 轴旋转的角度
	/// @param[in] roll  横摆是绕 z 轴旋转的角度
	static fcyMatrix4 GetRotationYawPitchRoll(
		const fFloat yaw,
		const fFloat pitch,
		const fFloat roll)
	{
		fFloat sin_x = sin(pitch);
		fFloat cos_x = cos(pitch);
		fFloat sin_y = sin(yaw);
		fFloat cos_y = cos(yaw);
		fFloat sin_z = sin(roll);
		fFloat cos_z = cos(roll);

		return fcyMatrix4(
			cos_y*cos_z, cos_y*sin_z, -sin_y, 0.f,
			sin_x*sin_y*cos_z - cos_x*sin_z, sin_x*sin_y*sin_z + cos_x*cos_z, sin_x*cos_y, 0.f,
			cos_x*sin_y*cos_z + sin_x*sin_z, cos_x*sin_y*sin_z - sin_x*cos_z, cos_x*cos_y, 0.f,
			0.f, 0.f, 0.f, 1.f
			);
	};
	/// @brief     右手系 返回绕任意轴旋转矩阵
	/// @param[in] axisRotation 旋转向量
	/// @param[in] angle        角度
	static fcyMatrix4 GetRotationAxisRH(
		const fcyVec3& axisRotation,  
		const fFloat angle)
	{
		fFloat angle_sin = sin(angle),
			angle_cos = cos(angle);

		return fcyMatrix4(
			angle_cos + ( 1 - angle_cos ) * axisRotation.x * axisRotation.x , 
			( 1 - angle_cos ) * axisRotation.x * axisRotation.y + axisRotation.z * angle_sin , 
			( 1 - angle_cos ) * axisRotation.x * axisRotation.z - axisRotation.y * angle_sin  , 
			0,

			( 1 - angle_cos ) * axisRotation.x * axisRotation.y - axisRotation.z * angle_sin , 
			angle_cos + ( 1 - angle_cos ) * axisRotation.y * axisRotation.y ,
			( 1 - angle_cos ) * axisRotation.y * axisRotation.z + axisRotation.x * angle_sin ,
			0,

			( 1 - angle_cos ) * axisRotation.x * axisRotation.z + axisRotation.y * angle_sin ,
			( 1 - angle_cos ) * axisRotation.y * axisRotation.z - axisRotation.x * angle_sin  , 
			angle_cos + ( 1 - angle_cos ) * axisRotation.z * axisRotation.z , 
			0,

			0 ,	0 ,	0 ,	1
			);
	};
	/// @brief     左手系 返回绕任意轴旋转矩阵
	/// @param[in] axisRotation 旋转向量
	/// @param[in] angle        角度
	static fcyMatrix4 GetRotationAxisLH(
		const fcyVec3& axisRotation,
		const fFloat angle)
	{
		fFloat angle_sin = sin(angle),
			angle_cos = cos(angle);

		return fcyMatrix4(
			angle_cos + ( 1 - angle_cos ) * axisRotation.x * axisRotation.x , 
			( 1 - angle_cos ) * axisRotation.x * axisRotation.y - axisRotation.z * angle_sin , 
			( 1 - angle_cos ) * axisRotation.x * axisRotation.z + axisRotation.y * angle_sin  , 
			0,

			( 1 - angle_cos ) * axisRotation.x * axisRotation.y + axisRotation.z * angle_sin , 
			angle_cos + ( 1 - angle_cos ) * axisRotation.y * axisRotation.y ,
			( 1 - angle_cos ) * axisRotation.y * axisRotation.z - axisRotation.x * angle_sin ,
			0,

			( 1 - angle_cos ) * axisRotation.x * axisRotation.z - axisRotation.y * angle_sin ,
			( 1 - angle_cos ) * axisRotation.y * axisRotation.z + axisRotation.x * angle_sin  , 
			angle_cos + ( 1 - angle_cos ) * axisRotation.z * axisRotation.z , 
			0,

			0 ,	0 ,	0 ,	1
			);
	};
	/// @brief     左手系 返回观察某点的矩阵
	/// @param[in] eye    眼睛位置
	/// @param[in] lookat 观察位置
	/// @param[in] up     上方向量
	static fcyMatrix4 GetLookAtLH(const fcyVec3& eye, const fcyVec3& lookat, const fcyVec3& up)
	{
		fcyVec3 zaxis(lookat - eye);
		zaxis.Normalize();
		fcyVec3 xaxis = up.Cross(zaxis);
		xaxis.Normalize();
		fcyVec3 yaxis = zaxis.Cross(xaxis);

		return fcyMatrix4(
			xaxis.x     ,  yaxis.x    ,  zaxis.x    ,  0.f,
			xaxis.y     ,  yaxis.y    ,  zaxis.y    ,  0.f,
			xaxis.z     ,  yaxis.z    ,  zaxis.z    ,  0.f,
			-(xaxis*eye), -(yaxis*eye), -(zaxis*eye),  1.f
			);
	};
	/// @brief     右手系 返回观察某点的矩阵
	/// @param[in] eye    眼睛位置
	/// @param[in] lookat 观察位置
	/// @param[in] up     上方向量
	static fcyMatrix4 GetLookAtRH(const fcyVec3& eye, const fcyVec3& lookat, const fcyVec3& up)
	{
		fcyVec3 xaxis(up);
		xaxis.Normalize();
		fcyVec3 zaxis(eye - lookat);
		zaxis.Normalize();
		xaxis = xaxis.Cross(zaxis);
		fcyVec3 yaxis = zaxis.Cross(xaxis);

		return fcyMatrix4(
			xaxis.x, yaxis.x, zaxis.x ,0.f ,
			xaxis.y, yaxis.y, zaxis.y ,0.f ,
			xaxis.z, yaxis.z, zaxis.z ,0.f ,
			-(xaxis*eye),-(yaxis*eye),-(zaxis*eye),1.f
			);
	};
	/// @brief     左手系 返回正投影矩阵
	/// @param[in] w         横向可视范围
	/// @param[in] h         纵向可视范围
	/// @param[in] nearPlane 最近距离
	/// @param[in] farPlane  最远距离
	static fcyMatrix4 GetOrthoLH(
		const fuInt w,
		const fuInt h,
		const fFloat nearPlane,
		const fFloat farPlane)
	{
		return fcyMatrix4(
			2.0f/w, 0.f, 0.f, 0.f,
			0.f, 2.0f/h, 0.f, 0.f,
			0.f, 0.f, 1.f /(farPlane-nearPlane), 0.f,
			0.f, 0.f, nearPlane/(nearPlane - farPlane), 1.f
			);
	};
	/// @brief     右手系 返回正投影矩阵
	/// @param[in] w         横向可视范围
	/// @param[in] h         纵向可视范围
	/// @param[in] nearPlane 最近距离
	/// @param[in] farPlane  最远距离
	static fcyMatrix4 GetOrthoRH(
		const fuInt w,
		const fuInt h,
		const fFloat nearPlane,
		const fFloat farPlane)
	{
		return fcyMatrix4(
			2.0f/w, 0.f, 0.f, 0.f,
			0.f, 2.0f/h, 0.f, 0.f,
			0.f, 0.f, 1.f /(nearPlane - farPlane), 0.f,
			0.f, 0.f, nearPlane/(nearPlane - farPlane), 1.f
			);
	};
	/// @brief     左手系 返回透视投影矩阵
	/// @param[in] ration    屏幕纵横比（宽：高）
	/// @param[in] fovY      纵向视野范围（弧度）
	/// @param[in] nearPlane 最近距离
	/// @param[in] farPlane  最远距离
	static fcyMatrix4 GetPespctiveLH(
		const fFloat ration,
		const fFloat fovY,
		const fFloat nearPlane,
		const fFloat farPlane)
	{
		fFloat t = 1.f / tan(fovY*0.5f);

		return fcyMatrix4(
			t/ration, 0.f, 0.f, 0.f,
			0.f, t, 0.f, 0.f,
			0.f, 0.f, farPlane/(farPlane-nearPlane), 1.f,
			0.f, 0.f, -( nearPlane*farPlane )/( farPlane-nearPlane ), 0.f
			);
	};
	/// @brief     右手系 返回透视投影矩阵
	/// @param[in] ration    屏幕纵横比（宽：高）
	/// @param[in] fovY      纵向视野范围（弧度）
	/// @param[in] nearPlane 最近距离
	/// @param[in] farPlane  最远距离
	static fcyMatrix4 GetPespctiveRH(
		const fFloat ration,
		const fFloat fovY,
		const fFloat nearPlane,
		const fFloat farPlane)
	{
		fFloat t = 1.f / tan(fovY*0.5f);

		return fcyMatrix4(
			t/ration, 0.f, 0.f, 0.f,
			0.f, t, 0.f, 0.f,
			0.f, 0.f, farPlane/(nearPlane-farPlane), -1.f,
			0.f, 0.f, ( nearPlane*farPlane )/( nearPlane-farPlane),	0.f
			);
	};
	/// @brief     左手系 返回自定义正交投影矩阵
	/// @param[in] l  最左侧X值
	/// @param[in] r  最右侧X值
	/// @param[in] b  最下方Y值
	/// @param[in] t  最上方Y值
	/// @param[in] zn 最近距离
	/// @param[in] zf 最远距离
	static fcyMatrix4 GetOrthoOffCenterLH(
		const fFloat l,
		const fFloat r,
		const fFloat b,
		const fFloat t,
		const fFloat zn,
		const fFloat zf)
	{
		return fcyMatrix4(
			2.f/(r-l)  , 0.f        , 0.f        , 0.f,
			0.f        , 2.f/(t-b)  , 0.f        , 0.f,
			0.f        , 0.f        , 1.f/(zf-zn), 0.f,
            (l+r)/(l-r), (t+b)/(b-t), zn/(zn-zf) , 1.f
			);
	};
	/// @brief     右手系 返回自定义正交投影矩阵
	/// @param[in] l  最左侧X值
	/// @param[in] r  最右侧X值
	/// @param[in] b  最下方Y值
	/// @param[in] t  最上方Y值
	/// @param[in] zn 最近距离
	/// @param[in] zf 最远距离
	static fcyMatrix4 GetOrthoOffCenterRH(
		const fFloat l,
		const fFloat r,
		const fFloat b,
		const fFloat t,
		const fFloat zn,
		const fFloat zf)
	{
		return fcyMatrix4(
			2.f/(r-l)  , 0.f        , 0.f        , 0.f,
			0.f        , 2.f/(t-b)  , 0.f        , 0.f,
			0.f        , 0.f        , 1.f/(zn-zf), 0.f,
			(l+r)/(l-r), (t+b)/(b-t), zn/(zn-zf) , 1.f
			);
	};
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 颜色值
////////////////////////////////////////////////////////////////////////////////
class fcyColor
{
public:
	union{
		fuInt argb;   ///< @brief 颜色值
		struct
		{
			fByte b;
			fByte g;
			fByte r;
			fByte a;
		};
	};
public: // 构造函数
	/// @brief 默认构造函数，产生Alpha=255的黑色
	fcyColor()
		: argb(0xFF000000) {}
	/// @brief 使用颜色值产生颜色
	fcyColor(fuInt ARGB)
		: argb(ARGB) {}
	/// @brief 使用RGB值产生颜色，A=255
	/// @param[in] R 取值为[0,255]
	/// @param[in] G 取值为[0,255]
	/// @param[in] B 取值为[0,255]
	fcyColor(fInt R, fInt G, fInt B)
		: a(255), r((fByte)R), g((fByte)G), b((fByte)B) {}
	/// @brief 使用ARGB值产生颜色
	/// @param[in] A 取值为[0,255]
	/// @param[in] R 取值为[0,255]
	/// @param[in] G 取值为[0,255]
	/// @param[in] B 取值为[0,255]
	fcyColor(fInt A, fInt R, fInt G, fInt B)
		: a((fByte)A), r((fByte)R), g((fByte)G), b((fByte)B) {}
	/// @brief     使用RGB浮点值产生颜色
	/// @param[in] R 取值为[0,1]
	/// @param[in] G 取值为[0,1]
	/// @param[in] B 取值为[0,1]
	fcyColor(fDouble R, fDouble G, fDouble B)
		: a((fByte)255), r((fByte)(R * 255)), g((fByte)(G * 255)), b((fByte)(B * 255)) {}
	/// @brief     使用RGB浮点值产生颜色
	/// @param[in] A 取值为[0,1]
	/// @param[in] R 取值为[0,1]
	/// @param[in] G 取值为[0,1]
	/// @param[in] B 取值为[0,1]
	fcyColor(fDouble A, fDouble R, fDouble G, fDouble B)
		: a((fByte)(A * 255)), r((fByte)(R * 255)), g((fByte)(G * 255)), b((fByte)(B * 255)) {}
public: // 函数
	/// @brief 设置新值
	void Set(fByte A, fByte R, fByte G, fByte B)
	{
		a = A;
		r = R;
		g = G;
		b = B;
	}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 矩形
////////////////////////////////////////////////////////////////////////////////
class fcyRect
{
public:
	fcyVec2 a;  ///< @brief 矩形左上角
	fcyVec2 b;  ///< @brief 矩形右下角
public:
	fcyRect() {}
	/// @brief     创建矩形
	/// @param[in] A 矩形左上角
	/// @param[in] B 矩形右下角
	fcyRect(const fcyVec2& A, const fcyVec2& B)
		: a(A), b(B) {}
	/// @brief     创建矩形
	/// @param[in] x1 左边
	/// @param[in] y1 顶边
	/// @param[in] x2 底边
	/// @param[in] y2 右边
	fcyRect(fFloat x1, fFloat y1, fFloat x2, fFloat y2)
		: a(x1,y1), b(x2,y2) {}
public:
	/// @brief 取宽度
	fFloat GetWidth()const
	{
		return fabs(a.x - b.x);
	}
	/// @brief 取高度
	fFloat GetHeight()const
	{
		return fabs(a.y - b.y);
	}
	/// @brief 是否包含点
	/// @note  含边界
	fBool Contain(const fcyVec2& x)const
	{
		return (x.x>=a.x && x.x<=b.x && x.y>=a.y && x.y<=b.y);
	}
	/// @brief 是否与圆相交
	/// @note  含相切
	fBool Contain(const fcyVec2& x, fFloat R)const
	{
		return (x.x + R >= a.x && x.x - R <=b.x && x.y + R >=a.y && x.y - R <=b.y);
	}
	/// @brief 获得中心点
	fcyVec2 GetCenter()const
	{
		return ((a+b)*0.5);
	}
	/// @brief      求是否相交，若相交返回公共部分
	/// @param[in]  Rect 待判断的矩形
	/// @param[out] pOut 输出的相交部分
	fBool Intersect(const fcyRect& Rect, fcyRect* pOut)
	{
		fcyRect tRet(
			FCYMAX(a.x, Rect.a.x),
			FCYMAX(a.y, Rect.a.y),
			FCYMIN(b.x, Rect.b.x),
			FCYMIN(b.y, Rect.b.y)
			);

		if(tRet.a.x <= tRet.b.x && tRet.a.y <= tRet.b.y)
		{
			// 相交
			if(pOut)
				*pOut = tRet;
			return true;
		}
		else
			return false;
	}
};

/// @}

