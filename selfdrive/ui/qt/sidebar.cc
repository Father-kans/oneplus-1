#include "selfdrive/ui/qt/sidebar.h"

#include <QMouseEvent>

#include "selfdrive/common/util.h"
#include "selfdrive/hardware/hw.h"
#include "selfdrive/ui/qt/util.h"

void Sidebar::drawMetric(QPainter &p, const QString &label, const QString &val, QColor c, int y) {
  const QRect rect = {30, y, 240, val.isEmpty() ? (label.contains("\n") ? 130 : 130) : 135};

  p.setPen(Qt::NoPen);
  p.setBrush(QBrush(c));
  p.setClipRect(rect.x() + 6, rect.y(), 18, rect.height(), Qt::ClipOperation::ReplaceClip);
  p.drawRoundedRect(QRect(rect.x() + 6, rect.y() + 6, 100, rect.height() - 12), 10, 10);
  p.setClipping(false);

  QPen pen = QPen(QColor(0xff, 0xff, 0xff, 0x55));
  pen.setWidth(2);
  p.setPen(pen);
  p.setBrush(Qt::NoBrush);
  p.drawRoundedRect(rect, 20, 20);

  p.setPen(QColor(0xff, 0xff, 0xff));
  if (val.isEmpty()) {
    configFont(p, "Open Sans", 40, "Regular");
    const QRect r = QRect(rect.x() + 35, rect.y(), rect.width() - 50, rect.height());
    p.drawText(r, Qt::AlignCenter, label);
  } else {
    configFont(p, "Open Sans", 58, "Regular");
    p.drawText(rect.x() + 50, rect.y() + 61, val);
    configFont(p, "Open Sans", 35, "Regular");
    p.drawText(rect.x() + 50, rect.y() + 35 + 77, label);
  }
}

Sidebar::Sidebar(QWidget *parent) : QFrame(parent) {
  home_img = QImage("../assets/images/button_home.png").scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  settings_img = QImage("../assets/images/button_settings.png").scaled(settings_btn.width(), settings_btn.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

  connect(this, &Sidebar::valueChanged, [=] { update(); });

  setAttribute(Qt::WA_OpaquePaintEvent);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
  setFixedWidth(300);
}

void Sidebar::mouseReleaseEvent(QMouseEvent *event) {
  if (settings_btn.contains(event->pos())) {
    emit openSettings();
  }
}

void Sidebar::updateState(const UIState &s) {
  auto &sm = *(s.sm);

  auto deviceState = sm["deviceState"].getDeviceState();
  setProperty("netType", network_type[deviceState.getNetworkType()]);
  int strength = (int)deviceState.getNetworkStrength();
  setProperty("netStrength", strength > 0 ? strength + 1 : 0);
  setProperty("wifiAddr", deviceState.getWifiIpAddress().cStr());

  bool online = net_type != network_type[cereal::DeviceState::NetworkType::NONE];
  setProperty("connectStr",  online ? "인터넷\n연결됨" : "인터넷\n오프라인");
  setProperty("connectStatus", online ? good_color : danger_color);
  m_battery_img = deviceState.getBatteryStatus() == "Charging" ? 1 : 0;
  m_batteryPercent = deviceState.getBatteryPercent();

  QColor tempStatus = danger_color;
  auto ts = deviceState.getThermalStatus();
  if (ts == cereal::DeviceState::ThermalStatus::GREEN) {
    tempStatus = good_color;
  } else if (ts == cereal::DeviceState::ThermalStatus::YELLOW) {
    tempStatus = warning_color;
  }
  setProperty("tempStatus", tempStatus);
  setProperty("tempVal", (int)deviceState.getAmbientTempC());

  QString pandaStr = "차량\n연결됨";
  QColor pandaStatus = good_color;
  if (s.scene.pandaType == cereal::PandaState::PandaType::UNKNOWN) {
    pandaStatus = danger_color;
    pandaStr = "차량\n연결안됨";
  } /*else if (s.scene.started && !sm["liveLocationKalman"].getLiveLocationKalman().getGpsOK()) {
    pandaStatus = warning_color;
    pandaStr = "GPS\n찾는중";
  }*/
  setProperty("pandaStr", pandaStr);
  setProperty("pandaStatus", pandaStatus);
}

void Sidebar::paintEvent(QPaintEvent *event) {
  QPainter p(this);
  p.setPen(Qt::NoPen);
  p.setRenderHint(QPainter::Antialiasing);

  //battery
  QRect  rect(45, 293, 96, 36);
  QRect  bq(50, 298, int(76* m_batteryPercent * 0.01), 25);
  QBrush bgBrush("#149948");
  p.fillRect(bq,  bgBrush);
  p.drawImage(rect, battery_imgs[m_battery_img]);

  p.setPen(Qt::white);
  configFont(p, "Open Sans", 30, "Regular");

  char battery_str[32];

  const QRect bt = QRect(170, 288, event->rect().width(), 50);
  snprintf(battery_str, sizeof(battery_str), "%d%%", m_batteryPercent);
  p.drawText(bt, Qt::AlignLeft, battery_str);

  // static imgs
  p.setOpacity(0.65);
  p.drawImage(settings_btn.x(), settings_btn.y(), settings_img);
  p.setOpacity(1.0);
  p.drawImage(60, 1080 - 180 - 40, home_img);

  // network
  int x = 58;
  const QColor gray(0x54, 0x54, 0x54);
  for (int i = 0; i < 5; ++i) {
    p.setBrush(i < net_strength ? Qt::white : gray);
    p.drawEllipse(x, 196, 27, 27);
    x += 37;
  }

  configFont(p, "Open Sans", 30, "Regular");
  p.setPen(QColor(0xff, 0xff, 0xff));

  const QRect r = QRect(-15, 237, event->rect().width(), 50);

  if(Hardware::EON() && net_type == network_type[cereal::DeviceState::NetworkType::WIFI])
    p.drawText(r, Qt::AlignCenter, wifi_addr);
  else
    p.drawText(r, Qt::AlignCenter, net_type);

  // metrics
  configFont(p, "Open Sans", 35, "Regular");
  drawMetric(p, "이온온도", QString("%1°C").arg(temp_val), temp_status, 355);
  drawMetric(p, panda_str, "", panda_status, 518);
  drawMetric(p, connect_str, "", connect_status, 676);
}
