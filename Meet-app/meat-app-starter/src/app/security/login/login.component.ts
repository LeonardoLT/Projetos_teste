import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { ActivatedRoute, Router } from '@angular/router';
import { NotificationService } from 'app/shared/messages/notification.service';
import { LoginService } from './login.service';
import { User } from "./user.model";

@Component({
  selector: 'mt-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {

  loginForm: FormGroup
  navigateTo: string

  constructor(private formbuilder: FormBuilder,
              private loginService: LoginService,
              private notificationService: NotificationService,
              private actvatedRoute: ActivatedRoute,
              private router: Router) { }

  ngOnInit() {
    this.loginForm = this.formbuilder.group({
      email: this.formbuilder.control('', [Validators.required, Validators.email]),
      password: this.formbuilder.control('', [Validators.required])
    })
    this.navigateTo = this.actvatedRoute.snapshot.params['to'] || '/'
  }

  login(){
    this.loginService.login(this.loginForm.value.email, this.loginForm.value.password)
                            .subscribe(user => this.notificationService.notify(`Bem vindo(a) ${user.name}`),
                                       response => this.notificationService.notify(response.error.message),
                                       () => {
                                         this.router.navigate([this.navigateTo])
                                       })
  }

}
