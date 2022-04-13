import { ActivatedRouteSnapshot, CanDeactivate, RouterStateSnapshot } from "@angular/router";
import { Observable } from "rxjs";
import { OrderComponent } from "./order.component";

export class LeaveOrderGuard implements CanDeactivate <OrderComponent>{  //O CanDeaxtivate espera qual componente ele vai ser implementado, por isso o OrderComponent está aqui

    canDeactivate(orderComponent: OrderComponent,
                  activatedRoute: ActivatedRouteSnapshot,
                  routerState: RouterStateSnapshot, nextState?: RouterStateSnapshot): boolean | Observable<boolean> | Promise<boolean> {

                    if(!orderComponent.isOrderCompleted()){
                        return window.confirm('Deseja desistir da compra?')
                    }else{
                        return true
                    }
        
    }
}