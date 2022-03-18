import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { CartItem } from 'app/restaurant-detail/shopping-cart/cart-item.model';
import { RadioOption } from 'app/shared/radio/radio-option.model';
import { Order, OrderItem } from './order.model';
import { OrderService } from './order.service';

@Component({
  selector: 'mt-order',
  templateUrl: './order.component.html'
})
export class OrderComponent implements OnInit {

  constructor(private orderService: OrderService, private router: Router) { }

  paymentOptions: RadioOption[] = [
    {label: 'Dinheiro', value: 'MON'},
    {label: 'Cartão de Débito', value: 'DEB'},
    {label: 'Vale Refeição', value: 'REF'}
  ];

  delivery: number = 8;

  ngOnInit() {
    
  }

  itemsValue(){
    return this.orderService.totalValue();
  }

  cartItems(): CartItem[]{
    return this.orderService.cartItems();
  }

  increaseQty(item: CartItem){
    this.orderService.increaseQty(item);
  }

  decreaseQty(item: CartItem){
    this.orderService.decreaseQty(item);
  }

  removeItem(item: CartItem){
    this.orderService.removeItem(item);
  }

  checkOrder(order: Order){
    order.orderItems = this.cartItems()
      .map((items:CartItem) => new OrderItem(items.quantity, items.menuItem.id)); //Pegando  cada item e transformando de CartItem para OrderItem
    this.orderService.checkOrder(order)
      .subscribe((orderId: string) => {
        this.router.navigate(['/order-summary'])
        console.log(`Compra concluída: ${orderId}`)
        this.orderService.clear()
      })
    console.log(order);
  }

}
