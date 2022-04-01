import { Injectable } from "@angular/core";
import { HttpClient } from "@angular/common/http";
import { MEAT_API } from "app/app.api";
import { ErrorHandler } from "app/app.error-handler";
import { CartItem } from "app/restaurant-detail/shopping-cart/cart-item.model";
import { ShoppingCartService } from "app/restaurant-detail/shopping-cart/shopping-cart.service";
import { Observable } from "rxjs/Observable";
import { Order } from "./order.model";

@Injectable()
export class OrderService{

    constructor(private shoppingCartService: ShoppingCartService, private http: HttpClient){} 
  
    cartItems(): CartItem[]{
        return this.shoppingCartService.items;
    }

    totalValue(): number{
        return this.shoppingCartService.total();
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

    clear(){
        this.shoppingCartService.clear();
    }

    checkOrder(order: Order): Observable<string>{
        return this.http.post<Order>(`${MEAT_API}/orders`, order)
            .map(order => order.id)
            .catch(ErrorHandler.handleError)
    }

}