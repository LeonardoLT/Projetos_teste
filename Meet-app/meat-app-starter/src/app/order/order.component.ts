import { Component, OnInit } from '@angular/core';
import { CartItem } from 'app/restaurant-detail/shopping-cart/cart-item.model';
import { ShoppingCartService } from 'app/restaurant-detail/shopping-cart/shopping-cart.service';
import { RadioOption } from 'app/shared/radio/radio-option.model';

@Component({
  selector: 'mt-order',
  templateUrl: './order.component.html'
})
export class OrderComponent implements OnInit {

  constructor(private shoppingCartService: ShoppingCartService) { }

  paymentOptions: RadioOption[] = [
    {label: 'Dinheiro', value: 'MON'},
    {label: 'Cartão de Débito', value: 'DEB'},
    {label: 'Vale Refeição', value: 'REF'}
  ];
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
