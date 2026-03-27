# BMS 测试资产目录

本目录承载 BMS 的样例 payload、mock、契约测试输入、联调记录和回归报告。

当前已落地完整的测试资产基线，对应：

1. Formal 01 到 Formal 11 的最小契约样例集。
2. 13 个工作包的测试资产入口说明。
3. 主业务闭环、运维治理、BFF 推送与恢复三类集成场景骨架。
4. platform、resource、simulation、message、monitor 五类 mock 入口。
5. contract、integration、regression 三类报告归档入口。

阅读顺序建议：

1. 先看 contract 目录中的正式 ICD 样例。
2. 再看 workPackages 目录中的工作包映射说明。
3. 最后看 integration/core_battle_loop 中的时序说明与验收模板。

## 当前说明

1. 所有 Formal ICD 均已具备正常、异常、边界最小样例。
2. 所有工作包均已具备测试资产入口说明。
3. 工作包到样例与联调场景的闭环映射见 [designArtifacts/delivery/BMS_WorkPackage_Test_Asset_Mapping.md](../designArtifacts/delivery/BMS_WorkPackage_Test_Asset_Mapping.md)。
