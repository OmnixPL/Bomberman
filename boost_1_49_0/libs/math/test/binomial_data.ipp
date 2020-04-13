//  (C) Copyright John Maddock 2006-7.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

   static const boost::array<boost::array<T, 3>, 159> binomial_data = { {
      {{ SC_(0.15e2), SC_(0.15e2), SC_(0.1e1) }}, 
      {{ SC_(0.19e2), SC_(0.15e2), SC_(0.3876e4) }}, 
      {{ SC_(0.19e2), SC_(0.19e2), SC_(0.1e1) }}, 
      {{ SC_(0.21e2), SC_(0.15e2), SC_(0.54264e5) }}, 
      {{ SC_(0.21e2), SC_(0.19e2), SC_(0.21e3) }}, 
      {{ SC_(0.21e2), SC_(0.21e2), SC_(0.1e1) }}, 
      {{ SC_(0.29e2), SC_(0.15e2), SC_(0.7755876e8) }}, 
      {{ SC_(0.29e2), SC_(0.19e2), SC_(0.2003001e8) }}, 
      {{ SC_(0.29e2), SC_(0.21e2), SC_(0.4292145e7) }}, 
      {{ SC_(0.29e2), SC_(0.29e2), SC_(0.1e1) }}, 
      {{ SC_(0.33e2), SC_(0.15e2), SC_(0.103715832e10) }}, 
      {{ SC_(0.33e2), SC_(0.19e2), SC_(0.8188092e9) }}, 
      {{ SC_(0.33e2), SC_(0.21e2), SC_(0.35481732e9) }}, 
      {{ SC_(0.33e2), SC_(0.29e2), SC_(0.4092e5) }}, 
      {{ SC_(0.33e2), SC_(0.33e2), SC_(0.1e1) }}, 
      {{ SC_(0.42e2), SC_(0.15e2), SC_(0.98672427616e11) }}, 
      {{ SC_(0.42e2), SC_(0.19e2), SC_(0.4467753108e12) }}, 
      {{ SC_(0.42e2), SC_(0.21e2), SC_(0.53825787444e12) }}, 
      {{ SC_(0.42e2), SC_(0.29e2), SC_(0.2551873128e11) }}, 
      {{ SC_(0.42e2), SC_(0.33e2), SC_(0.44589181e9) }}, 
      {{ SC_(0.42e2), SC_(0.42e2), SC_(0.1e1) }}, 
      {{ SC_(0.46e2), SC_(0.15e2), SC_(0.511738760544e12) }}, 
      {{ SC_(0.46e2), SC_(0.19e2), SC_(0.415424667196e13) }}, 
      {{ SC_(0.46e2), SC_(0.21e2), SC_(0.6943526580276e13) }}, 
      {{ SC_(0.46e2), SC_(0.29e2), SC_(0.174969502686e13) }}, 
      {{ SC_(0.46e2), SC_(0.33e2), SC_(0.10176623079e12) }}, 
      {{ SC_(0.46e2), SC_(0.42e2), SC_(0.163185e6) }}, 
      {{ SC_(0.46e2), SC_(0.46e2), SC_(0.1e1) }}, 
      {{ SC_(0.82e2), SC_(0.15e2), SC_(0.996731056598616e16) }}, 
      {{ SC_(0.82e2), SC_(0.19e2), SC_(0.19710382359693168e19) }}, 
      {{ SC_(0.82e2), SC_(0.21e2), SC_(0.1833065559451464624e20) }}, 
      {{ SC_(0.82e2), SC_(0.29e2), SC_(0.1257660762751009389168e23) }}, 
      {{ SC_(0.82e2), SC_(0.33e2), SC_(0.899986590548788671513e23) }}, 
      {{ SC_(0.82e2), SC_(0.42e2), SC_(0.41467066225715382349482e24) }}, 
      {{ SC_(0.82e2), SC_(0.46e2), SC_(0.23223183395337370425708e24) }}, 
      {{ SC_(0.82e2), SC_(0.82e2), SC_(0.1e1) }}, 
      {{ SC_(0.95e2), SC_(0.15e2), SC_(0.110375347398090219e18) }}, 
      {{ SC_(0.95e2), SC_(0.19e2), SC_(0.45038039715653129145e20) }}, 
      {{ SC_(0.95e2), SC_(0.21e2), SC_(0.611230538998149609825e21) }}, 
      {{ SC_(0.95e2), SC_(0.29e2), SC_(0.2146280142106099437545685e25) }}, 
      {{ SC_(0.95e2), SC_(0.33e2), SC_(0.3780222443838484815806271e26) }}, 
      {{ SC_(0.95e2), SC_(0.42e2), SC_(0.171987522327068244097964157e28) }}, 
      {{ SC_(0.95e2), SC_(0.46e2), SC_(0.308620560869098008873280965e28) }}, 
      {{ SC_(0.95e2), SC_(0.82e2), SC_(0.3489735464257595e16) }}, 
      {{ SC_(0.95e2), SC_(0.95e2), SC_(0.1e1) }}, 
      {{ SC_(0.122e3), SC_(0.15e2), SC_(0.6156937298378625264e19) }}, 
      {{ SC_(0.122e3), SC_(0.19e2), SC_(0.819751088529043274604e22) }}, 
      {{ SC_(0.122e3), SC_(0.21e2), SC_(0.205054879430622110547372e24) }}, 
      {{ SC_(0.122e3), SC_(0.29e2), SC_(0.965499981454662046766678536e28) }}, 
      {{ SC_(0.122e3), SC_(0.33e2), SC_(0.68890617994929806723272437813e30) }}, 
      {{ SC_(0.122e3), SC_(0.42e2), SC_(0.982048893026815201335532502524191e33) }}, 
      {{ SC_(0.122e3), SC_(0.46e2), SC_(0.9517963588769497111427223674615988e34) }}, 
      {{ SC_(0.122e3), SC_(0.82e2), SC_(0.254605268562507644790693611765531e33) }}, 
      {{ SC_(0.122e3), SC_(0.95e2), SC_(0.877923835320476575559398624e27) }}, 
      {{ SC_(0.122e3), SC_(0.122e3), SC_(0.1e1) }}, 
      {{ SC_(0.125e3), SC_(0.15e2), SC_(0.90648078331934398e19) }}, 
      {{ SC_(0.125e3), SC_(0.19e2), SC_(0.1350175763944140060675e23) }}, 
      {{ SC_(0.125e3), SC_(0.21e2), SC_(0.357796577445197116078875e24) }}, 
      {{ SC_(0.125e3), SC_(0.29e2), SC_(0.21471697865846785089593512375e29) }}, 
      {{ SC_(0.125e3), SC_(0.33e2), SC_(0.1743111472200107189546091504625e31) }}, 
      {{ SC_(0.125e3), SC_(0.42e2), SC_(0.339619764433637564049548277312025e34) }}, 
      {{ SC_(0.125e3), SC_(0.46e2), SC_(0.38244450869782214079034893241053e35) }}, 
      {{ SC_(0.125e3), SC_(0.82e2), SC_(0.655545126697486460839825744579025e34) }}, 
      {{ SC_(0.125e3), SC_(0.95e2), SC_(0.687094331707097122866992396e29) }}, 
      {{ SC_(0.125e3), SC_(0.122e3), SC_(0.31775e6) }}, 
      {{ SC_(0.125e3), SC_(0.125e3), SC_(0.1e1) }}, 
      {{ SC_(0.135e3), SC_(0.15e2), SC_(0.307563739414613748e20) }}, 
      {{ SC_(0.135e3), SC_(0.19e2), SC_(0.65183278299357679461e23) }}, 
      {{ SC_(0.135e3), SC_(0.21e2), SC_(0.2070345077412932009547e25) }}, 
      {{ SC_(0.135e3), SC_(0.29e2), SC_(0.2654598483954587033449048188e30) }}, 
      {{ SC_(0.135e3), SC_(0.33e2), SC_(0.322268385697858320141605625441e32) }}, 
      {{ SC_(0.135e3), SC_(0.42e2), SC_(0.165539796634100865734488051471458e36) }}, 
      {{ SC_(0.135e3), SC_(0.46e2), SC_(0.2961867439565318449706072684149998e37) }}, 
      {{ SC_(0.135e3), SC_(0.82e2), SC_(0.1323968752490674447090425029339391282e39) }}, 
      {{ SC_(0.135e3), SC_(0.95e2), SC_(0.319215598884570762368184126129732e35) }}, 
      {{ SC_(0.135e3), SC_(0.122e3), SC_(0.437531400061434e18) }}, 
      {{ SC_(0.135e3), SC_(0.125e3), SC_(0.393812684240976e15) }}, 
      {{ SC_(0.135e3), SC_(0.135e3), SC_(0.1e1) }}, 
      {{ SC_(0.137e3), SC_(0.15e2), SC_(0.388194525997363728e20) }}, 
      {{ SC_(0.137e3), SC_(0.19e2), SC_(0.87968625327656981292e23) }}, 
      {{ SC_(0.137e3), SC_(0.21e2), SC_(0.28916543839848387707556e25) }}, 
      {{ SC_(0.137e3), SC_(0.29e2), SC_(0.4280069137507949602563401336e30) }}, 
      {{ SC_(0.137e3), SC_(0.33e2), SC_(0.560540007685072462740701644251e32) }}, 
      {{ SC_(0.137e3), SC_(0.42e2), SC_(0.3453905364934565879468064249738192e36) }}, 
      {{ SC_(0.137e3), SC_(0.46e2), SC_(0.67381580139170956477318127290699344e37) }}, 
      {{ SC_(0.137e3), SC_(0.95e2), SC_(0.3453905364934565879468064249738192e36) }}, 
      {{ SC_(0.137e3), SC_(0.122e3), SC_(0.388194525997363728e20) }}, 
      {{ SC_(0.137e3), SC_(0.125e3), SC_(0.55587257066498976e17) }}, 
      {{ SC_(0.137e3), SC_(0.135e3), SC_(0.9316e4) }}, 
      {{ SC_(0.137e3), SC_(0.137e3), SC_(0.1e1) }}, 
      {{ SC_(0.143e3), SC_(0.15e2), SC_(0.76435265515004093841e20) }}, 
      {{ SC_(0.143e3), SC_(0.19e2), SC_(0.210374461432936964163e24) }}, 
      {{ SC_(0.143e3), SC_(0.21e2), SC_(0.76395982994646537557478e25) }}, 
      {{ SC_(0.143e3), SC_(0.29e2), SC_(0.17138496567725350060390313738e31) }}, 
      {{ SC_(0.143e3), SC_(0.33e2), SC_(0.27947962468928852152878073112114e33) }}, 
      {{ SC_(0.143e3), SC_(0.42e2), SC_(0.291038363317011408088847346619471914e37) }}, 
      {{ SC_(0.143e3), SC_(0.46e2), SC_(0.728184459077800535203086713053471437e38) }}, 
      {{ SC_(0.143e3), SC_(0.95e2), SC_(0.3005697554491346889987208985795179974e39) }}, 
      {{ SC_(0.143e3), SC_(0.122e3), SC_(0.76395982994646537557478e25) }}, 
      {{ SC_(0.143e3), SC_(0.125e3), SC_(0.31976918137806418552776e23) }}, 
      {{ SC_(0.143e3), SC_(0.135e3), SC_(0.3553074951283e13) }}, 
      {{ SC_(0.143e3), SC_(0.137e3), SC_(0.10679057389e11) }}, 
      {{ SC_(0.143e3), SC_(0.143e3), SC_(0.1e1) }}, 
      {{ SC_(0.144e3), SC_(0.15e2), SC_(0.85323087086516197776e20) }}, 
      {{ SC_(0.144e3), SC_(0.19e2), SC_(0.242351379570743382715776e24) }}, 
      {{ SC_(0.144e3), SC_(0.21e2), SC_(0.89439199603488629335584e25) }}, 
      {{ SC_(0.144e3), SC_(0.29e2), SC_(0.214603783108908731190974363328e31) }}, 
      {{ SC_(0.144e3), SC_(0.33e2), SC_(0.36256816175907700090220202956256e33) }}, 
      {{ SC_(0.144e3), SC_(0.42e2), SC_(0.410877689388721987890137430521607408e37) }}, 
      {{ SC_(0.144e3), SC_(0.46e2), SC_(0.1069985327624523235400453945711223336e39) }}, 
      {{ SC_(0.144e3), SC_(0.122e3), SC_(0.500046434146777336739856e26) }}, 
      {{ SC_(0.144e3), SC_(0.125e3), SC_(0.242351379570743382715776e24) }}, 
      {{ SC_(0.144e3), SC_(0.135e3), SC_(0.56849199220528e14) }}, 
      {{ SC_(0.144e3), SC_(0.137e3), SC_(0.219683466288e12) }}, 
      {{ SC_(0.144e3), SC_(0.143e3), SC_(0.144e3) }}, 
      {{ SC_(0.144e3), SC_(0.144e3), SC_(0.1e1) }}, 
      {{ SC_(0.145e3), SC_(0.15e2), SC_(0.95168058673421912904e20) }}, 
      {{ SC_(0.145e3), SC_(0.19e2), SC_(0.27889642887109357534752e24) }}, 
      {{ SC_(0.145e3), SC_(0.21e2), SC_(0.10458616082666009075532e26) }}, 
      {{ SC_(0.145e3), SC_(0.29e2), SC_(0.26825472888613591398871795416e31) }}, 
      {{ SC_(0.145e3), SC_(0.33e2), SC_(0.4693962808488050458108865561301e33) }}, 
      {{ SC_(0.145e3), SC_(0.42e2), SC_(0.57842004816858920625310609151100072e37) }}, 
      {{ SC_(0.145e3), SC_(0.46e2), SC_(0.156715022732884716296026082957704428e39) }}, 
      {{ SC_(0.145e3), SC_(0.122e3), SC_(0.315246665005577016640344e27) }}, 
      {{ SC_(0.145e3), SC_(0.125e3), SC_(0.1757047501887889524689376e25) }}, 
      {{ SC_(0.145e3), SC_(0.135e3), SC_(0.824313388697656e15) }}, 
      {{ SC_(0.145e3), SC_(0.137e3), SC_(0.398176282647e13) }}, 
      {{ SC_(0.145e3), SC_(0.143e3), SC_(0.1044e5) }}, 
      {{ SC_(0.145e3), SC_(0.144e3), SC_(0.145e3) }}, 
      {{ SC_(0.145e3), SC_(0.145e3), SC_(0.1e1) }}, 
      {{ SC_(0.148e3), SC_(0.15e2), SC_(0.131439605927052712464e21) }}, 
      {{ SC_(0.148e3), SC_(0.19e2), SC_(0.42244624913775365779698e24) }}, 
      {{ SC_(0.148e3), SC_(0.21e2), SC_(0.16608172537529972375104128e26) }}, 
      {{ SC_(0.148e3), SC_(0.29e2), SC_(0.51863815313548295889610045344e31) }}, 
      {{ SC_(0.148e3), SC_(0.33e2), SC_(0.100644585365316213131406856592232e34) }}, 
      {{ SC_(0.148e3), SC_(0.42e2), SC_(0.1587255130729102485141868921944628536e38) }}, 
      {{ SC_(0.148e3), SC_(0.122e3), SC_(0.6418858594895863473128136624e29) }}, 
      {{ SC_(0.148e3), SC_(0.125e3), SC_(0.525225250880542723214261376e27) }}, 
      {{ SC_(0.148e3), SC_(0.135e3), SC_(0.1525832904625819216e19) }}, 
      {{ SC_(0.148e3), SC_(0.137e3), SC_(0.12775329171405528e17) }}, 
      {{ SC_(0.148e3), SC_(0.143e3), SC_(0.552689424e9) }}, 
      {{ SC_(0.148e3), SC_(0.144e3), SC_(0.19190605e8) }}, 
      {{ SC_(0.148e3), SC_(0.145e3), SC_(0.529396e6) }}, 
      {{ SC_(0.148e3), SC_(0.148e3), SC_(0.1e1) }}, 
      {{ SC_(0.149e3), SC_(0.15e2), SC_(0.146152994650230254904e21) }}, 
      {{ SC_(0.149e3), SC_(0.19e2), SC_(0.484188393242502269321154e24) }}, 
      {{ SC_(0.149e3), SC_(0.21e2), SC_(0.19332950844468483467894649e26) }}, 
      {{ SC_(0.149e3), SC_(0.29e2), SC_(0.643975706809891340629324729688e31) }}, 
      {{ SC_(0.149e3), SC_(0.33e2), SC_(0.129276234650276859970513979588298e34) }}, 
      {{ SC_(0.149e3), SC_(0.42e2), SC_(0.2210289854940525890524658592240650952e38) }}, 
      {{ SC_(0.149e3), SC_(0.122e3), SC_(0.35422590023684579907262679888e30) }}, 
      {{ SC_(0.149e3), SC_(0.125e3), SC_(0.3260773432550036073288539376e28) }}, 
      {{ SC_(0.149e3), SC_(0.135e3), SC_(0.16239221627803361656e20) }}, 
      {{ SC_(0.149e3), SC_(0.137e3), SC_(0.158627003878285306e18) }}, 
      {{ SC_(0.149e3), SC_(0.143e3), SC_(0.13725120696e11) }}, 
      {{ SC_(0.149e3), SC_(0.144e3), SC_(0.571880029e9) }}, 
      {{ SC_(0.149e3), SC_(0.145e3), SC_(0.19720001e8) }}, 
      {{ SC_(0.149e3), SC_(0.148e3), SC_(0.149e3) }}, 
      {{ SC_(0.149e3), SC_(0.149e3), SC_(0.1e1) }}
   } };

