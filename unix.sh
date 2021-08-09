#!/usr/bin/bash

sed -i -e 's/\r$//' /data/openpilot/selfdrive/*.py
sed -i -e 's/\r$//' /data/openpilot/selfdrive/manager/*.py
sed -i -e 's/\r$//' /data/openpilot/selfdrive/car/*.py
sed -i -e 's/\r$//' /data/openpilot/selfdrive/ui/*.cc, *.h
sed -i -e 's/\r$//' /data/openpilot/selfdrive/controls/*.py
sed -i -e 's/\r$//' /data/openpilot/selfdrive/controls/lib/*.py
sed -i -e 's/\r$//' /data/openpilot/cereal/*.py
sed -i -e 's/\r$//' /data/openpilot/cereal/*.cc
sed -i -e 's/\r$//' /data/openpilot/cereal/*.capnp
sed -i -e 's/\r$//' /data/openpilot/selfdrive/car/gm/*.py
sed -i -e 's/\r$//' /data/openpilot/selfdrive/ui/qt/*.cc
sed -i -e 's/\r$//' /data/openpilot/selfdrive/ui/qt/*.h
sed -i -e 's/\r$//' /data/openpilot/selfdrive/ui/qt/offroad/*.cc
sed -i -e 's/\r$//' /data/openpilot/selfdrive/ui/qt/widgets/*.h
sed -i -e 's/\r$//' /data/openpilot/selfdrive/ui/qt/offroad/*.cc
sed -i -e 's/\r$//' /data/openpilot/selfdrive/ui/qt/widgets/*.h
sed -i -e 's/\r$//' /data/openpilot/selfdrive/controls/lib/lead_mpc_lib/*.py
sed -i -e 's/\r$//' /data/openpilot/selfdrive/controls/lib/lead_mpc_lib/lib_mpc_export/*.h
sed -i -e 's/\r$//' /data/openpilot/selfdrive/controls/lib/lead_mpc_lib/*.c
sed -i -e 's/\r$//' /data/openpilot/selfdrive/controls/lib/lead_mpc_lib/lib_mpc_export/*.c
sed -i -e 's/\r$//' /data/openpilot/selfdrive/boardd/*.cc
sed -i -e 's/\r$//' /data/openpilot/selfdrive/boardd/*.pyx
sed -i -e 's/\r$//' /data/openpilot/selfdrive/boardd/*.h
sed -i -e 's/\r$//' /data/openpilot/selfdrive/boardd/*.py
sed -i -e 's/\r$//' /data/openpilot/selfdrive/camerad/cameras/*.h
sed -i -e 's/\r$//' /data/openpilot/selfdrive/camerad/cameras/*.cc
sed -i -e 's/\r$//' /data/openpilot/selfdrive/camerad/snapshot/*.py
sed -i -e 's/\r$//' /data/openpilot/selfdrive/camerad/*.cc
sed -i -e 's/\r$//' /data/openpilot/selfdrive/thermald/*.py
sed -i -e 's/\r$//' /data/openpilot/selfdrive/athena/*.py
sed -i -e 's/\r$//' /data/openpilot/common/*.py
sed -i -e 's/\r$//' /data/openpilot/common/*.pyx
sed -i -e 's/\r$//' /data/openpilot/common/*.pxd
sed -i -e 's/\r$//' /data/openpilot/launch_chffrplus.sh
sed -i -e 's/\r$//' /data/openpilot/launch_env.sh
sed -i -e 's/\r$//' /data/openpilot/launch_openpilot.sh
sed -i -e 's/\r$//' /data/openpilot/Jenkinsfile
sed -i -e 's/\r$//' /data/openpilot/SConstruct
sed -i -e 's/\r$//' /data/openpilot/t.sh
