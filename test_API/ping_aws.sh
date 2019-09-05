#!/bin/bash
curl --tlsv1.2 \
--cacert AmazonRootCA1.pem \
--cert efd713718e-certificate.pem.crt \
--key efd713718e-private.pem.key \
-X GET https://a16bnyd1eg3wsb-ats.iot.us-west-2.amazonaws.com:8443\
/things/test/shadow