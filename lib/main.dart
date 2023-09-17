import 'package:flutter/material.dart';
import 'package:health/pages/heart.dart';
import 'pages/loading.dart';
import 'pages/home.dart';
import 'pages/search.dart';
import 'pages/lungs.dart';
import 'pages/prescription.dart';
import 'pages/info.dart';

void main() => runApp(
      MaterialApp(
        initialRoute: '/',
        routes: {
          '/': (context) => const Home(),
          '/loading': (context) => const Loading(),
          '/search': (context) => const Search(),
          '/heart': (context) => const Heart(),
          '/lungs': (context) => const Lungs(),
          '/prescription': (context) => const Prescription(),
          '/info': (context) => const Info(),
        },
      ),
    );
