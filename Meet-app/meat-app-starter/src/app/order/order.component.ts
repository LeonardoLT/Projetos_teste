import { Component, OnInit } from '@angular/core';
import { CartItem } from 'app/restaurant-detail/shopping-cart/cart-item.model';
import { ShoppingCartService } from 'app/restaurant-detail/shopping-cart/shopping-cart.service';

@Component({
  selector: 'mt-order',
  templateUrl: './order.component.html'
})
export class OrderComponent implements OnInit {

  constructor(private shoppingCartService: ShoppingCartService) { }

  orderItems: CartItem[];
  quantity: number = 1;

  ngOnInit() {
    this.orderItems = this.shoppingCartService.items;
  }

  increaseItem(){
    this.quantity++;
  }

  decreaseItem(){
    this.quantity--;
  }

}
