/*
	Copyright (C) 2021 DeSmuME team

	This file is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with the this software.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GPU_OPERATIONS_AVX2_H
#define GPU_OPERATIONS_AVX2_H

#include "GPU_Operations.h"

#ifndef ENABLE_AVX2
	#warning This header requires AVX2 support.
#else

class ColorOperation_AVX2
{
public:
	ColorOperation_AVX2() {};
	
	FORCEINLINE v256u16 blend(const v256u16 &colA, const v256u16 &colB, const v256u16 &blendEVA, const v256u16 &blendEVB) const;
	template<NDSColorFormat COLORFORMAT, bool USECONSTANTBLENDVALUESHINT> FORCEINLINE v256u32 blend(const v256u32 &colA, const v256u32 &colB, const v256u16 &blendEVA, const v256u16 &blendEVB) const;
	
	FORCEINLINE v256u16 blend3D(const v256u32 &colA_Lo, const v256u32 &colA_Hi, const v256u16 &colB) const;
	template<NDSColorFormat COLORFORMAT> FORCEINLINE v256u32 blend3D(const v256u32 &colA, const v256u32 &colB) const;
	
	FORCEINLINE v256u16 increase(const v256u16 &col, const v256u16 &blendEVY) const;
	template<NDSColorFormat COLORFORMAT> FORCEINLINE v256u32 increase(const v256u32 &col, const v256u16 &blendEVY) const;
	
	FORCEINLINE v256u16 decrease(const v256u16 &col, const v256u16 &blendEVY) const;
	template<NDSColorFormat COLORFORMAT> FORCEINLINE v256u32 decrease(const v256u32 &col, const v256u16 &blendEVY) const;
};

class PixelOperation_AVX2
{
protected:
	template<NDSColorFormat OUTPUTFORMAT, bool ISDEBUGRENDER> FORCEINLINE void _copy16(GPUEngineCompositorInfo &compInfo, const v256u8 &srcLayerID, const v256u16 &src1, const v256u16 &src0) const;
	template<NDSColorFormat OUTPUTFORMAT, bool ISDEBUGRENDER> FORCEINLINE void _copy32(GPUEngineCompositorInfo &compInfo, const v256u8 &srcLayerID, const v256u32 &src3, const v256u32 &src2, const v256u32 &src1, const v256u32 &src0) const;
	
	template<NDSColorFormat OUTPUTFORMAT, bool ISDEBUGRENDER> FORCEINLINE void _copyMask16(GPUEngineCompositorInfo &compInfo, const v256u8 &passMask8, const v256u8 &srcLayerID, const v256u16 &src1, const v256u16 &src0) const;
	template<NDSColorFormat OUTPUTFORMAT, bool ISDEBUGRENDER> FORCEINLINE void _copyMask32(GPUEngineCompositorInfo &compInfo, const v256u8 &passMask8, const v256u8 &srcLayerID, const v256u32 &src3, const v256u32 &src2, const v256u32 &src1, const v256u32 &src0) const;
	
	template<NDSColorFormat OUTPUTFORMAT> FORCEINLINE void _brightnessUp16(GPUEngineCompositorInfo &compInfo, const v256u16 &evy16, const v256u8 &srcLayerID, const v256u16 &src1, const v256u16 &src0) const;
	template<NDSColorFormat OUTPUTFORMAT> FORCEINLINE void _brightnessUp32(GPUEngineCompositorInfo &compInfo, const v256u16 &evy16, const v256u8 &srcLayerID, const v256u32 &src3, const v256u32 &src2, const v256u32 &src1, const v256u32 &src0) const;
	
	template<NDSColorFormat OUTPUTFORMAT> FORCEINLINE void _brightnessUpMask16(GPUEngineCompositorInfo &compInfo, const v256u8 &passMask8, const v256u16 &evy16, const v256u8 &srcLayerID, const v256u16 &src1, const v256u16 &src0) const;
	template<NDSColorFormat OUTPUTFORMAT> FORCEINLINE void _brightnessUpMask32(GPUEngineCompositorInfo &compInfo, const v256u8 &passMask8, const v256u16 &evy16, const v256u8 &srcLayerID, const v256u32 &src3, const v256u32 &src2, const v256u32 &src1, const v256u32 &src0) const;
	
	template<NDSColorFormat OUTPUTFORMAT> FORCEINLINE void _brightnessDown16(GPUEngineCompositorInfo &compInfo, const v256u16 &evy16, const v256u8 &srcLayerID, const v256u16 &src1, const v256u16 &src0) const;
	template<NDSColorFormat OUTPUTFORMAT> FORCEINLINE void _brightnessDown32(GPUEngineCompositorInfo &compInfo, const v256u16 &evy16, const v256u8 &srcLayerID, const v256u32 &src3, const v256u32 &src2, const v256u32 &src1, const v256u32 &src0) const;
	
	template<NDSColorFormat OUTPUTFORMAT> FORCEINLINE void _brightnessDownMask16(GPUEngineCompositorInfo &compInfo, const v256u8 &passMask8, const v256u16 &evy16, const v256u8 &srcLayerID, const v256u16 &src1, const v256u16 &src0) const;
	template<NDSColorFormat OUTPUTFORMAT> FORCEINLINE void _brightnessDownMask32(GPUEngineCompositorInfo &compInfo, const v256u8 &passMask8, const v256u16 &evy16, const v256u8 &srcLayerID, const v256u32 &src3, const v256u32 &src2, const v256u32 &src1, const v256u32 &src0) const;
	
	template<NDSColorFormat OUTPUTFORMAT, GPULayerType LAYERTYPE>
	FORCEINLINE void _unknownEffectMask16(GPUEngineCompositorInfo &compInfo,
										  const v256u8 &passMask8,
										  const v256u16 &evy16,
										  const v256u8 &srcLayerID,
										  const v256u16 &src1, const v256u16 &src0,
										  const v256u8 &srcEffectEnableMask,
										  const v256u8 &dstBlendEnableMaskLUT,
										  const v256u8 &enableColorEffectMask,
										  const v256u8 &spriteAlpha,
										  const v256u8 &spriteMode) const;
	
	template<NDSColorFormat OUTPUTFORMAT, GPULayerType LAYERTYPE>
	FORCEINLINE void _unknownEffectMask32(GPUEngineCompositorInfo &compInfo,
										  const v256u8 &passMask8,
										  const v256u16 &evy16,
										  const v256u8 &srcLayerID,
										  const v256u32 &src3, const v256u32 &src2, const v256u32 &src1, const v256u32 &src0,
										  const v256u8 &srcEffectEnableMask,
										  const v256u8 &dstBlendEnableMaskLUT,
										  const v256u8 &enableColorEffectMask,
										  const v256u8 &spriteAlpha,
										  const v256u8 &spriteMode) const;
	
public:
	PixelOperation_AVX2() {};
	
	template <GPUCompositorMode COMPOSITORMODE, NDSColorFormat OUTPUTFORMAT, GPULayerType LAYERTYPE, bool WILLPERFORMWINDOWTEST>
	FORCEINLINE void Composite16(GPUEngineCompositorInfo &compInfo,
								 const bool didAllPixelsPass,
								 const v256u8 &passMask8,
								 const v256u16 &evy16,
								 const v256u8 &srcLayerID,
								 const v256u16 &src1, const v256u16 &src0,
								 const v256u8 &srcEffectEnableMask,
								 const v256u8 &dstBlendEnableMaskLUT,
								 const u8 *__restrict enableColorEffectPtr,
								 const u8 *__restrict sprAlphaPtr,
								 const u8 *__restrict sprModePtr) const;
	
	template <GPUCompositorMode COMPOSITORMODE, NDSColorFormat OUTPUTFORMAT, GPULayerType LAYERTYPE, bool WILLPERFORMWINDOWTEST>
	FORCEINLINE void Composite32(GPUEngineCompositorInfo &compInfo,
								 const bool didAllPixelsPass,
								 const v256u8 &passMask8,
								 const v256u16 &evy16,
								 const v256u8 &srcLayerID,
								 const v256u32 &src3, const v256u32 &src2, const v256u32 &src1, const v256u32 &src0,
								 const v256u8 &srcEffectEnableMask,
								 const v256u8 &dstBlendEnableMaskLUT,
								 const u8 *__restrict enableColorEffectPtr,
								 const u8 *__restrict sprAlphaPtr,
								 const u8 *__restrict sprModePtr) const;
};

#endif // ENABLE_AVX2

#endif // GPU_OPERATIONS_AVX2_H
