import 'package:flutter/material.dart';

class Heart extends StatefulWidget {
  const Heart({Key? key}) : super(key: key);

  @override
  State<Heart> createState() => _HeartState();
}

class _HeartState extends State<Heart> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Colors.indigo,
        title: const Text('REMOTE HEALTH MONITOR'),
        centerTitle: true,
      ),
      body: Column(
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: <Widget>[
          //title
          Container(
            alignment: Alignment.center,
            color: Colors.white60,
            height: 48.0,
            child: const Text(
              'HEART AUSCULTATION',
              style: TextStyle(
                height: 2,
                fontSize: 20,
                color: Colors.indigo,
                fontWeight: FontWeight.bold,
              ),
            ),
          ),
          //image
          Container(
            margin: const EdgeInsets.fromLTRB(20.0, 10.0, 20.0, 10.0),
            height: 300,
            width: 40,
            decoration: const BoxDecoration(
              image: DecorationImage(
                  image: AssetImage('image/heart.png'), fit: BoxFit.fitHeight),
            ),
          ),
          Expanded(
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: <Widget>[
                Container(
                  alignment: Alignment.center,
                  height: 60.0,
                  width: 100,
                  margin: const EdgeInsets.all(25.0),
                  child: FloatingActionButton.extended(
                    onPressed: () {},
                    label: const Text(
                      'A',
                      style: TextStyle(fontSize: 30, color: Colors.white),
                    ),
                  ),
                ),
                Container(
                  alignment: Alignment.center,
                  height: 60.0,
                  width: 100,
                  margin: const EdgeInsets.all(25.0),
                  child: FloatingActionButton.extended(
                    onPressed: () {},
                    label: const Text(
                      'P',
                      style: TextStyle(fontSize: 30, color: Colors.white),
                    ),
                  ),
                ),
              ],
            ),
          ),
          Expanded(
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: <Widget>[
                Container(
                  alignment: Alignment.center,
                  height: 60.0,
                  width: 100,
                  margin: const EdgeInsets.all(25.0),
                  child: FloatingActionButton.extended(
                    onPressed: () {},
                    label: const Text(
                      'T',
                      style: TextStyle(fontSize: 30, color: Colors.white),
                    ),
                  ),
                ),
                Container(
                  alignment: Alignment.center,
                  height: 60.0,
                  width: 100,
                  margin: const EdgeInsets.all(25.0),
                  child: FloatingActionButton.extended(
                    onPressed: () {},
                    label: const Text(
                      'E',
                      style: TextStyle(fontSize: 30, color: Colors.white),
                    ),
                  ),
                ),
              ],
            ),
          ),
          Expanded(
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: <Widget>[
                Container(
                  alignment: Alignment.center,
                  height: 60.0,
                  width: 100,
                  margin: const EdgeInsets.all(25.0),
                  child: FloatingActionButton.extended(
                    onPressed: () {},
                    label: const Text(
                      'M',
                      style: TextStyle(fontSize: 30, color: Colors.white),
                    ),
                  ),
                ),
                Container(
                  alignment: Alignment.center,
                  height: 60.0,
                  width: 100,
                  margin: const EdgeInsets.all(25.0),
                  child: FloatingActionButton.extended(
                    onPressed: () {},
                    label: const Text(
                      '@',
                      style: TextStyle(fontSize: 30, color: Colors.white),
                    ),
                  ),
                ),
              ],
            ),
          ),

          Expanded(
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                Container(
                  alignment: Alignment.center,
                  height: 60.0,
                  width: 100,
                  margin: const EdgeInsets.all(10.0),
                  child: FloatingActionButton.extended(
                    onPressed: () {
                      Navigator.pushNamed(context, '/lungs');
                    },
                    icon: const Icon(Icons.favorite, size: 30.0),
                    backgroundColor: Colors.indigo,
                    label: const Text(
                      'Lungs',
                      style: TextStyle(fontSize: 10, color: Colors.white),
                    ),
                  ),
                ),
                Container(
                  alignment: Alignment.center,
                  height: 60.0,
                  width: 100,
                  margin: const EdgeInsets.all(10.0),
                  child: FloatingActionButton.extended(
                    onPressed: () {
                      Navigator.pushNamed(context, '/info');
                    },
                    icon: const Icon(Icons.badge, size: 30.0),
                    backgroundColor: Colors.indigo,
                    label: const Text(
                      'info',
                      style: TextStyle(fontSize: 10, color: Colors.white),
                    ),
                  ),
                ),
                Container(
                  alignment: Alignment.center,
                  height: 60.0,
                  width: 100,
                  margin: const EdgeInsets.all(10.0),
                  child: FloatingActionButton.extended(
                    onPressed: () {
                      Navigator.pushNamed(context, '/prescription');
                    },
                    icon: const Icon(Icons.medication, size: 30.0),
                    backgroundColor: Colors.indigo,
                    label: const Text(
                      'Pres',
                      style: TextStyle(fontSize: 10, color: Colors.white),
                    ),
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}
