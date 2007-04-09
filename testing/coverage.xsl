<?xml version="1.0" encoding="utf-8"?>
<!-- XSL Test Suite Coverage table cell module -->
<!-- $Id: coverage.xsl,v 1.1 2004/01/30 12:24:08 tonygraham Exp $ -->

<!-- Author: Tony Graham <Tony.Graham@Ireland.Sun.com> -->
<!-- Created: 5 June 2001 -->
<!-- Version: $Revision: 1.1 $ -->
<!--
     $Log: coverage.xsl,v $
     Revision 1.1  2004/01/30 12:24:08  tonygraham
     Templates for reporting test coverage.

     Revision 1.2  2001/06/29 10:35:32  mf
     Updated from top-level makefile

     Revision 1.1  2001/06/19 10:06:22  mf
     updated

     Revision 1.1  2001/06/05 14:03:42  tg127171
     Initial revision

-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <xsl:template name="coverage-styles">
    th.full {background-color: green; color: white; text-align: center}
    th.future {background-color: palegreen; text-align: center}
    th.differ {background-color: yellow; text-align: center}
    th.test {background-color: orange; text-align: center}
    th.spec {background-color: red; text-align: center}
    th.other {background-color: white; text-align: center}
    td.full {background-color: green; color: white; text-align: center}
    td.future {background-color: palegreen; text-align: center}
    td.differ {background-color: yellow; text-align: center}
    td.test {background-color: orange; text-align: center}
    td.spec {background-color: red; text-align: center}
    td.other {background-color: white; text-align: center}
    a.full {color: white; text-decoration: none}
    a.future {color: black; text-decoration: none}
    a.differ {color: black; text-decoration: none}
    a.test {color: black; text-decoration: none}
    a.spec {color: black; text-decoration: none}
    a.other {color: black; text-decoration: none}
  </xsl:template>

  <xsl:template name="coverage-summary-table">
    <table border="1">
      <tr>
        <td class="full" width="10%">Full</td>
        <td>Full agreement with the expected result and no
        problems reported with either the spec or the test</td>
      </tr>
      <tr>
        <td class="future" width="10%">Future</td>
        <td>The test result differed from the expected result but
        future support is expected. Full agreement with the
        expected result was not reported, no problem with either
        the spec or the test was reported, and future support of
        the feature tested by this test case is expected</td>
      </tr>
      <tr>
        <td class="differ" width="10%">Differ</td>
        <td>The test result differed from the expected
        result. Full agreement with the expected result was not
        reported, no problem with either the spec or the test was
        reported, and no expected future support of the feature
        tested by this test case was reported</td>
      </tr>
      <tr>
        <td class="test" width="10%">Test</td>
        <td>Full agreement with the expected result was not
        reported and a problem with the test was reported</td>
      </tr>
      <tr>
        <td class="spec" width="10%">Spec</td>
        <td>Full agreement with the expected result was not
        reported and a problem with the spec was reported</td>
      </tr>
      <tr>
        <td class="other" width="10%">&#160;</td>
        <td>The test result file does not cover this test</td>
      </tr>
    </table>
  </xsl:template>

  <xsl:template name="coverage-cell">
    <xsl:param name="width"/>
    <xsl:param name="result"/>
    <xsl:param name="result-html-href"/>
    <xsl:param name="result-cell-width" select="'100%'"/>

    <xsl:choose>
      <xsl:when test="$result/@agreement = 'full' and
                      $result/@specproblem = 'no' and
                      $result/@testproblem = 'no'">
        <td width="{$result-cell-width}" class="full">
          <xsl:choose>
            <xsl:when test="$result-html-href">
              <a class="full" href="{$result-html-href}">Full</a>
            </xsl:when>
            <xsl:otherwise>Full</xsl:otherwise>
          </xsl:choose>
        </td>
      </xsl:when>
      <xsl:when test="$result/@agreement = 'issues' and
                      $result/@specproblem = 'no' and
                      $result/@testproblem = 'no'">
        <xsl:choose>
          <xsl:when test="$result/@futuresupport = 'full' or
                          $result/@futuresupport = 'partial'">
            <td width="{$result-cell-width}" class="future">
              <xsl:choose>
                <xsl:when test="$result-html-href">
                  <a class="future" href="{$result-html-href}">Future</a>
                </xsl:when>
                <xsl:otherwise>Future</xsl:otherwise>
              </xsl:choose>
            </td>
          </xsl:when>
          <xsl:otherwise>
            <td width="{$result-cell-width}" class="differ">
              <xsl:choose>
                <xsl:when test="$result-html-href">
                  <a class="differ" href="{$result-html-href}">Differ</a>
                </xsl:when>
                <xsl:otherwise>Differ</xsl:otherwise>
              </xsl:choose>
            </td>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:when>
      <xsl:when test="$result/@testproblem = 'yes' and
                      $result/@specproblem = 'no'">
        <td width="{$result-cell-width}" class="test">
          <xsl:choose>
            <xsl:when test="$result-html-href">
              <a class="test" href="{$result-html-href}">Test</a>
            </xsl:when>
            <xsl:otherwise>Test</xsl:otherwise>
          </xsl:choose>
        </td>
      </xsl:when>
      <xsl:when test="$result/@specproblem = 'yes'">
        <td width="{$result-cell-width}" class="spec">
          <xsl:choose>
            <xsl:when test="$result-html-href">
              <a class="spec" href="{$result-html-href}">Spec</a>
            </xsl:when>
            <xsl:otherwise>Spec</xsl:otherwise>
          </xsl:choose>
        </td>
      </xsl:when>
      <xsl:otherwise>
        <td width="{$result-cell-width}" class="other">
          <xsl:choose>
            <xsl:when test="$result">
              <xsl:choose>
                <xsl:when test="$result-html-href">
                  <a href="{$result-html-href}">Other</a>
                </xsl:when>
                <xsl:otherwise>Other</xsl:otherwise>
              </xsl:choose>
            </xsl:when>
            <xsl:otherwise>&#160;</xsl:otherwise>
          </xsl:choose>
        </td>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

</xsl:stylesheet>
