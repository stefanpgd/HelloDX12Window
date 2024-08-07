#pragma once

#include "Graphics/DXCommon.h"

class DXDescriptorHeap
{
public:
	DXDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE type, unsigned int numberOfDescriptors,
		D3D12_DESCRIPTOR_HEAP_FLAGS flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE);

	ComPtr<ID3D12DescriptorHeap> Get();
	ID3D12DescriptorHeap* GetAddress();
	CD3DX12_CPU_DESCRIPTOR_HANDLE GetCPUHandleAt(unsigned int index);
	CD3DX12_GPU_DESCRIPTOR_HANDLE GetGPUHandleAt(unsigned int index);

	unsigned int GetNextAvailableIndex();
	unsigned int GetDescriptorSize();

private:
	ComPtr<ID3D12DescriptorHeap> descriptorHeap;

	unsigned int descriptorSize;
	unsigned int descriptorCount;
	unsigned int currentDescriptorIndex = 0;
};