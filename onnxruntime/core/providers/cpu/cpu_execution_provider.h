// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "core/framework/allocatormgr.h"
#include "core/framework/execution_provider.h"
#include "core/graph/constants.h"

namespace onnxruntime {

// Information needed to construct CPU execution providers.
struct CPUExecutionProviderInfo {
  bool create_arena{true};

  explicit CPUExecutionProviderInfo(bool use_arena)
      : create_arena(use_arena) {}

  CPUExecutionProviderInfo() = default;
};

using FuseRuleFn = std::function<void(const onnxruntime::GraphViewer&,
                                      std::vector<std::unique_ptr<ComputeCapability>>&)>;

// Logical device representation.
class CPUExecutionProvider : public IExecutionProvider {
 public:
  explicit CPUExecutionProvider(const CPUExecutionProviderInfo& /*info*/)
      : IExecutionProvider{onnxruntime::kCpuExecutionProvider} {}

  std::shared_ptr<KernelRegistry> GetKernelRegistry() const override;


 private:
  std::vector<FuseRuleFn> fuse_rules_;
};
}  // namespace onnxruntime
