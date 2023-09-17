import 'package:flutter/material.dart';

class Lungs extends StatefulWidget {
  const Lungs({Key? key}) : super(key: key);

  @override
  State<Lungs> createState() => _LungsState();
}

class _LungsState extends State<Lungs> {
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
              'LUNGS AUSCULTATION',
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
                  image: AssetImage('image/lung1.png'), fit: BoxFit.fitHeight),
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
                      'L1',
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
                      'R1',
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
                      'L2',
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
                      'R2',
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
                      'L3',
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
                      'R3',
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
                      Navigator.pushNamed(context, '/heart');
                    },
                    icon: const Icon(Icons.favorite, size: 30.0),
                    backgroundColor: Colors.indigo,
                    label: const Text(
                      'Heart',
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
