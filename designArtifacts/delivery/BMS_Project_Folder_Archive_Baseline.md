# BMS 项目文件夹统一归档基线

本文档用于把当前项目文件夹中的全部设计、契约、样例、评审和交付资产归入统一基线，作为后续开发工作的固定参考入口。

## 1. 根目录归档原则

根目录仅保留 7 类内容：

1. 需求源。
2. 架构图稿。
3. 设计与交付资产。
4. 测试与样例资产。
5. 旧系统参考资产。
6. proto 试验资产。
7. 本地环境资产。

## 2. 根目录结构说明

### 2.1 sysFunctionalRequirements

用途：原始需求源。

归档要求：

1. 只放原始需求文档与脑图。
2. 不放派生设计和交付文档。

### 2.2 plantumlC4

用途：全部架构图稿与代码设计图。

归档要求：

1. L0/L1/L2/L3/Dynamic/Deployment/Supplementary/Code 图统一在此归档。
2. 该目录只承载图稿，不承载交付说明与测试样例。

### 2.3 designArtifacts

用途：全部派生设计资产主目录。

子层划分如下：

1. contracts：语义与契约层。
2. icd：正式 ICD 层。
3. schema：schema / IDL / proto 工程化层。
4. review：审查与旧系统参考评估层。
5. delivery：交付、治理、执行、归档、完成基线层。

### 2.4 testAssets

用途：全部执行资产主目录。

子层划分如下：

1. contract：按 Formal ICD 分组的契约样例。
2. workPackages：按工作包分组的测试入口与包级说明。
3. integration：跨工作包联调场景与验收模板。
4. mocks：对外部依赖和子系统输入的 mock。
5. reports：契约、联调、回归报告归档。

### 2.5 oldSysReference

用途：旧系统参考资料。

归档要求：

1. 只能作为参考输入。
2. 不得与当前正式 ICD 混放。

### 2.6 proto

用途：proto 与试验性 schema 资产。

归档要求：

1. 只放工程化和演化过程文件。
2. 不直接替代正式 ICD 文档。

### 2.7 .venv

用途：本地 Python 运行环境。

归档要求：

1. 不属于设计基线。
2. 不作为交付资产的一部分。

## 3. 设计基线入口

后续开发统一从以下入口读取：

1. 总导航：[BMS_Design_Artifact_Guide.md](../../BMS_Design_Artifact_Guide.md)
2. delivery 分类导航：[README.md](README.md)
3. 设计目标：[BMS_System_Design_Goal.md](BMS_System_Design_Goal.md)
4. 完成定义：[BMS_Completion_Definition.md](BMS_Completion_Definition.md)
5. 设计完成关口：[BMS_Design_Completion_Gate_And_Dev_Start_Criteria.md](BMS_Design_Completion_Gate_And_Dev_Start_Criteria.md)
6. 工作包索引：[BMS_Execution_Index.md](BMS_Execution_Index.md)
7. 测试映射：[BMS_WorkPackage_Test_Asset_Mapping.md](BMS_WorkPackage_Test_Asset_Mapping.md)

## 4. 后续开发归档规则

1. 新设计文档优先进入 designArtifacts 对应分层目录。
2. 新样例、mock、验收模板、回归结果统一进入 testAssets。
3. 工作包专属说明优先放在 workPackages 对应子目录。
4. 不再允许把新的派生文档散落回 sysFunctionalRequirements。
5. 不再允许把测试样例放到 designArtifacts 中。

## 5. 当前基线结论

截至当前，项目文件夹已完成统一归档分层，后续开发应以上述目录职责为固定基线，不再随意改动主结构。
