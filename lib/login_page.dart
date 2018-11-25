import 'package:flutter/material.dart';


class LoginPage extends StatefulWidget {

  @override
  _LoginPageState createState() => _LoginPageState();
}

class _LoginPageState extends State<LoginPage> {
  static TextEditingController _controller = TextEditingController();
  static mostrarUser = ' ';

  final vacio = Container(
    padding: EdgeInsets.only(
      top: 120.0,
      bottom: 10.0
    ),
  );
  final logo = Center(///creamos la variable para el logo
    child: Image.asset('assets/logo.png', height: 150.0,),
  );


  final user = Container(
    padding: EdgeInsets.only(
        right: 32.0,
        left: 32.0,
        bottom: 16.0,
        top: 80.0
    ),
    child: TextField(
      controller: _controller,
    ),
  );
  final pass = Container(
    padding: EdgeInsets.only(
        right: 32.0,
        left: 32.0,
        bottom: 16.0
    ),
    child: TextField(
      controller: _controller,
    ),
  );
  final boton = RaisedButton(
    onPressed: (){
      setState(() {
        mostrarUser = _controller.text;
      });
    },
    child: Text('Commencer'),);

  final mostrar = Container(
    child: Text(mostrarUser),
  );
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body:
      Column(
        children: <Widget>[
          vacio,
          logo,
          user,
          mostrar,
          pass,
          boton,
        ],
      ),
    );
  }
}