#pragma once

#include "Graphics/DXCommon.h"
#include "Graphics/Window.h"

#include <cstdint>

class DXCommands
{
public:
	DXCommands(D3D12_COMMAND_LIST_TYPE type, unsigned int commandAllocatorCount);
	~DXCommands();

	void ExecuteCommandList(int allocatorIndex = 0);
	void ResetCommandList(int allocatorIndex = 0);

	void Signal();
	void Flush();
	void WaitForFenceValue(unsigned int allocatorIndex = 0);

	ComPtr<ID3D12CommandQueue> GetCommandQueue();
	ComPtr<ID3D12CommandList> GetCommandList();
	ComPtr<ID3D12GraphicsCommandList4> GetGraphicsCommandList();

private:
	void CreateCommandQueue(D3D12_COMMAND_LIST_TYPE type);
	void CreateCommandList();
	void CreateCommandAllocators();
	void CreateSynchronizationObjects();

private:
	ComPtr<ID3D12Device5> device;

	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12GraphicsCommandList4> commandList;
	ComPtr<ID3D12CommandAllocator> commandAllocators[Window::BackBufferCount];

	// CPU-GPU Synchronization //
	unsigned int commandAllocatorCount = 0;
	ComPtr<ID3D12Fence> fence;
	HANDLE fenceEvent;
	uint64_t* frameFenceValues = nullptr;
	uint64_t fenceValue = 0;
};