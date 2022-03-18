import { Injectable } from "@angular/core";
import { CartItem } from "app/restaurant-detail/shopping-cart/cart-item.model";
import { ShoppingCartService } from "app/restaurant-detail/shopping-cart/shopping-cart.service";

@Injectable()
export class OrderService{

    constructor(private shoppingCartService: ShoppingCartService){} 
  
    cartItems(): CartItem[]{
        return this.shoppingCartService.items;
    }

    increaseQty(item: CartItem){
        this.shoppingCartService.increaseQty(item);
    }

    decreaseQty(item: CartItem){
        this.shoppingCartService.decreaseQty(item);
    }

    removeItem(item: CartItem){
        this.shoppingCartService.removeItem(item);
    }

}