#!/bin/sh

cd `dirname $0`

java -Xmx500M -Xms200M \
     -Dlogback.configurationFile=conf/logback.xml \
     -DentityExpansionLimit=100000000 \
     -Dfile.encoding=UTF-8 \
     -XX:CompileCommand=exclude,javax/swing/text/GlyphView,getBreakSpot \
     -classpath bundles/guava.jar:bundles/logback-classic.jar:bundles/logback-core.jar:bundles/slf4j-api.jar:bin/org.apache.felix.main.jar:bin/protege-launcher.jar \
     $CMD_OPTIONS org.protege.osgi.framework.Launcher $1



