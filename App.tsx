import React, { useEffect, useState } from 'react';
import {
  Button,
  NativeModules,
  StatusBar,
  StyleSheet,
  Text,
  useColorScheme,
  View,
} from 'react-native';

import { MathOperationsProxy } from './src/mathops/MathOperationsProxy';
import { SafeAreaProvider, SafeAreaView } from 'react-native-safe-area-context';

function App(): React.JSX.Element {
  const isDarkMode = useColorScheme() === 'dark';
  const [jsiReady, setJsiReady] = useState(false);

  const backgroundStyle = {
    backgroundColor: isDarkMode ? '#1c1c1e' : '#f2f2f7',
    flex: 1,
  };

  const textColor = isDarkMode ? '#ffffff' : '#000000';

  useEffect(() => {
    // Bootstrap: native module installs global.MathOperationsProxy via JSI.
    // install() may return undefined in New Architecture; global is the source of truth.
    NativeModules.JSIExampleInstaller?.install?.();
    setJsiReady(global.MathOperationsProxy != null);
  }, []);

  return (
    <SafeAreaProvider>
      <SafeAreaView style={backgroundStyle}>
        <StatusBar
          barStyle={isDarkMode ? 'light-content' : 'dark-content'}
          backgroundColor={backgroundStyle.backgroundColor}
        />
        <View style={styles.container}>
          <Text style={[styles.title, { color: textColor }]}>JSI Example</Text>
          <Text style={[styles.subtitle, { color: textColor }]}>
            Manual HostObject bootstrap demo
          </Text>
          <Text style={[styles.jsiStatus, { color: textColor }]}>
            JSI status: {jsiReady ? 'installed' : 'pending'}
          </Text>
          <Button
            title="All Math Operations"
            disabled={!jsiReady}
            onPress={() => {
              console.log('global - sum', MathOperationsProxy.sum(10, 3));
              console.log(
                'global - subtract',
                MathOperationsProxy.subtract(10, 3),
              );
              console.log(
                'global - multiply',
                MathOperationsProxy.multiply(10, 3),
              );
              console.log('global - divide', MathOperationsProxy.divide(10, 3));
              console.log(
                'global - addGlobalVariables',
                MathOperationsProxy.addGlobalVariables(),
              );
            }}
          />
        </View>
      </SafeAreaView>
    </SafeAreaProvider>
  );
}

const styles = StyleSheet.create({
  container: {
    padding: 24,
    gap: 16,
  },
  title: {
    fontSize: 28,
    fontWeight: '700',
  },
  subtitle: {
    fontSize: 16,
  },
  jsiStatus: {
    fontSize: 16,
    fontWeight: '600',
  },
});

export default App;
