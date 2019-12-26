目的：要实现GraphicsView中多个item之间的层次调整功能，即：选中的item可以实现"移动至顶层、移动至底层、上移一层、下移一层"等功能。

        之前盲目地认为Qt API会提供“获取与之相邻的sibling item”类似这样的接口，但是查询无果。。。

        setZValue()设置item的栈顺序，通过zValue()来测试，具有低z-values的item比具有高z-value的item先绘制。（即：低z-values的item位于下层，高z-values的item位于上层）

        可以调用setZvalue()来设置一个item的Z值。默认的Z值是0，具有同样的Z值的item会按照插入的顺序来入栈(stack order)。也就是说，GraphicsView会优先根据item的Z值决定item的层次，只有当Z值相同的情况下才会去理会stack order；这样，我就基本上决定放弃采用setZvalue()方法来实现我的功能了，因为，由于所有item的Z值默认都是0，调用setZvalue()方法基本上只能实现置于顶层或底层的功能，即使想办法获取到了与其相邻的上一个或下一个item，也是需要去设置相关item的Z值，这样一来，维护tiem的层次的工作完全由自己来完成了，而不再是GraphicsSene自己去根据stack
order去管理维护了，自己的工作量会很大，而且，效率会比较低下。。。于是，果断放弃此途径。

        还是想偷个赖，把item的维护工作依然交给Scene，所以通过调整item的stack order来实现上述功能。

       API有一个stackBefore(QGraphicsItem *sibling) 方法，可以调用该访求来重新排序item的列表，就可以直接调整item的顺序了。例如：itemA->stackBefore(itemB)，是将itemA的order重置到itemB之前，这样，先绘制itemA，后绘制itemB，itemB处于上方。但是，这需要我解决“获取sibling item”的工作，还好问题不大，QGraphicsScene类方法collidingItems(QGraphicsItem *item)会返回一个在这个Scene中与传入的item有碰撞的所有其它item的一个列表QList<QGraphicsItem
*>，注意一下，这个列表是不包含item本身的，而且以是自上层向下层的顺序来返回的。

        于是，自己写了一个算法，以获取当前item在所有冲撞items中的位置，如下所示：

 

[cpp:nogutter] view
plaincopy
int QDrawGraphicsScene::getItemIndex(QGraphicsItem *item)  
{  
    //list1是与item碰撞的其它item列表  
    QList<QGraphicsItem *> list1 = collidingItems(item);  
  
    //没有碰撞  
    if (list1.size() == 0)  
        return 0;  
  
    //只有一个与之碰撞  
    if (list1.size() == 1)                     //共2层  
    {  
        QRectF rect1(item->mapToScene(item->boundingRect()).boundingRect());  
        QRectF rect2(list1.first()->mapToScene(list1.first()->boundingRect()).boundingRect());  
        QRectF rectMix = rect1.intersected(rect2);  
        QPointF point(item->mapFromScene(rectMix).boundingRect().center());  
        QRectF rect(point.x()-0.5, point.y()-0.5, 1, 1);  
        if (item->isObscured(rect))  
            return 1;                                //item为下层（共2层）  
        else  
            return 0;                                //item为顶层（共2层）                              
    }  
  
    //ist2是与list1末点碰撞的其它item列表  
    QList<QGraphicsItem *> list2 = collidingItems(list1.last());  
  
    if (list1.first() != list2.first())           //与之碰撞2个以上，且item位于顶层  
        return 0;  
    else  
    {  
        //ist3是与list1起点碰撞的其它item列表  
        QList<QGraphicsItem *> list3 = collidingItems(list1.first());  
        return (list3.indexOf(item) + 1);                            //返回该item的具体位置  
    }  
}  
 

算法中的难点是只有两层(即list1.size()为1)的时候判断哪个item在上，哪个在下，为此费尽周折，最终采用碰撞混和区域是否被覆盖的方法来实现判断两个item的上下关系。(完全使用碰撞混和区域会出问题，是因为转换后的区域并未完全覆盖，通过查看源码，覆盖判断很严格，所以取了混和区域的一个中心小区域进行判断，呃。。。汗一把ToT)

注意：为了便于表达，此函数返回的值是该item在与其他碰撞item共同组成的列表中的位置，即，该item也是其中之一；而，collidingItems(QGraphicsItem *item)返回的列表是不包含传入进去的item的，了解了这个，下面的调用才不会出问题。

以下是我简单写的一个小demo，以作测试：


具体的调用：

/**************************************************************************
* @file   		slotLayerUpper
* @brief		将所传入的图元上移一层
* @param		QGraphicsItem *itemSelected 要进行操作的图元
* @return		void
* @note			void
* @author		赵向前
* @date			2019/8/24
***************************************************************************/
void QDrawGraphicsScene::slotLayerUpper(QGraphicsItem *itemSelected)  
{  
    QList<QGraphicsItem *> collideItems = collidingItems(itemSelected);  
    if (collideItems.size() == 0)  
        return;  
    int nCurIndex = getItemIndex(itemSelected);  
    if (nCurIndex == 0)  
        return;  
    collideItems.at(nCurIndex - 1)->stackBefore(itemSelected);  
    update();  
}  
  
/**************************************************************************
* @file   		slotLayerLower
* @brief		将所传入的图元下移一层
* @param		QGraphicsItem *itemSelected 要进行操作的图元
* @return		void
* @note			void
* @author		赵向前
* @date			2019/8/24
***************************************************************************/
void QDrawGraphicsScene::slotLayerLower(QGraphicsItem *itemSelected)  
{  
    QList<QGraphicsItem *> items = selectedItems();  
    QGraphicsItem *itemSelected = items.first();  
    QList<QGraphicsItem *> collideItems = collidingItems(itemSelected);  
    if (collideItems.size() == 0)  
        return;  
    int nCurIndex = getItemIndex(itemSelected);  
    if (nCurIndex == collideItems.size())  
        return;  
    itemSelected->stackBefore(collideItems.at(nCurIndex));  
    update();  
}  
  
/**************************************************************************
* @file   		slotLayerTop
* @brief		将所传入的图元置于顶层
* @param		QGraphicsItem *itemSelected 要进行操作的图元
* @return		void
* @note			void
* @author		赵向前
* @date			2019/8/24
***************************************************************************/
void QDrawGraphicsScene::slotLayerTop()  
{  
    QList<QGraphicsItem *> collideItems = collidingItems(itemSelected);  
    for (int i = collideItems.size()-1; i >= 0; --i)  
        collideItems.at(i)->stackBefore(itemSelected);  
    update();  
}  
  
/**************************************************************************
* @file   		slotLayerBottom
* @brief		将所传入的图元置于底层
* @param		QGraphicsItem *itemSelected 要进行操作的图元
* @return		void
* @note			void
* @author		赵向前
* @date			2019/8/24
***************************************************************************/
void QDrawGraphicsScene::slotLayerBottom()  
{  
    QList<QGraphicsItem *> collideItems = collidingItems(itemSelected);  
    for (int i = 0; i < collideItems.size(); ++i)  
        itemSelected->stackBefore(collideItems.at(i));  
    update();  
}