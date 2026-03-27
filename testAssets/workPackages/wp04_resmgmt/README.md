# WP04 ResMgmt 测试资产说明

本目录用于说明 ResMgmt 当前已落地的最小测试资产入口。

## 1. 当前映射

1. ../../contract/formal03_resource_allocation_and_reservation/
2. ../../integration/core_battle_loop/

## 2. 重点验证内容

1. AllocationRequest 到 AllocationDecision.accepted 的正常链路。
2. 部分满足、预留和拒绝场景下的裁定语义。
3. accepted 不等于完全满足。
4. ResMgmt 是唯一资源裁定结果 owner。

## 3. 当前使用建议

1. 先阅读 Formal 03 的正常、异常和边界样例。
2. 再结合主业务闭环场景 A 和 B 的验收重点，检查 ResourceStateSnapshot 与 AllocationDecision 的边界。
3. 若后续补充链路质量相关测试，应在本说明中补充 Formal 07 对应入口。
