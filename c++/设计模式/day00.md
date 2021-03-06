##面向对象设计原则

隔离变化，将变化带来的影响最小

各尽其责，变化导致新类型的增加不应该影响原来的类型

##八大设计原则

1. 依赖倒置
	* 高层模块不应该依赖低层模块，二者应该依赖于抽象
	* 抽象不应该依赖细节，细节应该依赖于抽象
	* 高层，抽象是稳定的，细节和低层都是变化的。变化应该依赖于稳定。----隔离变化
2. 开放封闭
	* 对扩展开放，对更改封闭
	* 类模块可扩展，但不可修改
3. 单一职责
	* 一个类应该仅有一个引起它变化的原因
	* 变化方向隐含类的责任
4. Liskov替换
	* 子类必须能够替换它们的基类----父类能够使用的场景子类也应该能够胜任
	* 继承表达类型抽象
5. 接口隔离
	* 不应该强迫客户程序依赖它们不用的方法
	* 接口应该小而完备 ----不能无节制的public   应用程序容易产生依赖否则接口应该保持稳定
6. 优先使用组合，而不是继承
	* 继承 ---- 白箱复用      组合 ---- 黑箱复用
	* 继承通常会破坏封闭性，子类父类耦合度高
	* 组合只要有良好定义的接口就可以降低耦合度
7. 封装变化点
	* 使用封装创建对象之间的封闭层，让设计者在封闭层的一边修改而不会对另一边造成不良影响
8. 针对接口而不是针对实现
	* 业务中变量声明不能为具体类型，而是声明成某个抽象类型
	* 客户程序不需要知道具体类型，只需要知道接口
	* 实现“高内聚，松耦合”

八大原则中往往违背一个原则后也会违背其他原则


