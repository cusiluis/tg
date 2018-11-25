import 'package:flutter/material.dart';
import 'package:terra_group/login_page.dart';

void main(){
  runApp(
      MaterialApp(
        theme: ThemeData(//aqui definimos detalles para el theme como colores de texto, font family, etc
            accentColor: Colors.cyan[600],
            primaryColor: Colors.cyan
        ),
        home: LoginPage(),
      )
  );
}
