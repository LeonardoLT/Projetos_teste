import { Component, OnInit } from '@angular/core';
import { AbstractControl, FormBuilder, FormGroup, Validators } from '@angular/forms';
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

  orderForm: FormGroup;
  emailPattern = /^(([^<>()\[\]\.,;:\s@\"]+(\.[^<>()\[\]\.,;:\s@\"]+)*)|(\".+\"))@(([^<>()[\]\.,;:\s@\"]+\.)+[^<>()[\]\.,;:\s@\"]{2,})$/i;
  numberPattern = /^[0-9]*$/;

  constructor(private orderService: OrderService, private router: Router, private formbuilder: FormBuilder) { }

  paymentOptions: RadioOption[] = [
    {label: 'Dinheiro', value: 'MON'},
    {label: 'Cartão de Débito', value: 'DEB'},
    {label: 'Vale Refeição', value: 'REF'}
  ];

  delivery: number = 8;

  ngOnInit() {
    this.orderForm = this.formbuilder.group({
      name: this.formbuilder.control('', [Validators.required, Validators.minLength(5)]),
      email: this.formbuilder.control('', [Validators.required, Validators.pattern(this.emailPattern)]),
      emailConfirmation: this.formbuilder.control('', [Validators.required, Validators.pattern(this.emailPattern)]),
      address: this.formbuilder.control('', [Validators.required, Validators.minLength(5)]),
      number: this.formbuilder.control('', [Validators.required, Validators.pattern(this.numberPattern)]),
      optionalAddress: this.formbuilder.control(''),
      paymentOption: this.formbuilder.control('', [Validators.required])
    }, {validator: OrderComponent.equalsTo})
  }

  static equalsTo(group: AbstractControl): {[key:string]: boolean}{
    const email = group.get('email');
    const emailConfirmation = group.get('emailConfirmation');
    if(!email || !emailConfirmation){
      return undefined;
    }
    if(email.value !== emailConfirmation.value){
      return {emailsNotMatch:true}; //O nome da chave fui eu quem criou
    }
    return undefined;
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
