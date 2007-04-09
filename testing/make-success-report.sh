#!/bin/bash
perl dotests.pl .
perl png+ref2stereo.pl .
perl testsuccess.pl . > testsuccess.xml
make index.html
