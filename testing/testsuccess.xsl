<?xml version="1.0" encoding="utf-8"?>
<!-- XSL stylesheet to generate testsuccess.html from testresults.xml and
     testsuccess.xml. -->
<!-- Usage:
     xsltproc -o index.html -novalid testsuccess.xsl testsuccess.xsl
-->

<!-- Copyright (C) 2001 Sun Microsystems -->
<!-- Copyright (C) 2007-2009 Menteith Consulting Ltd -->

<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:exsl="http://exslt.org/common"
                extension-element-prefixes="exsl"
                version="1.0">

  <xsl:import href="config.xsl"/>
  <xsl:import href="common.xsl"/>
  
  <xsl:import href="coverage.xsl"/>
  <xsl:import href="results-doc.xsl"/>
  
  <xsl:output method="html" indent="no" encoding="UTF-8"/>

  <xsl:strip-space elements="*"/>

  <xsl:variable name="testsuccess-node"
    select="document($TESTSUCCESS)/testsuccess"/>

  <!-- Set of filenames - probably relative - of the testsuite.xml files -->
  <xsl:variable name="testsuite-files"
    select="document($TESTSUITES)/testsuites/testsuite/@href"/>

  <!-- Set of <testsuite> nodes -->
  <xsl:variable name="testsuite-nodes"
    select="document($testsuite-files, document($TESTSUITES))/testsuite"/>

  <xsl:variable name="testresults-doc"
    select="document($TEST_RESULTS)"/>
  <xsl:key name="results" match="testresult" use="@results"/>
  <xsl:key name="PDF" match="pdf" use="@name"/>

  <xsl:variable name="not-verified-string"
    select="'Results not yet verified'"/>

  <!-- Common navigation table component -->
  <xsl:template name="nav-table">
    <xsl:param name="up-id"/>
    <xsl:param name="top-id"/>

    <xsl:if test="$up-id or $top-id">
      <table align="right" class="navtable">
        <tr>
          <td align="right">
            <xsl:if test="$up-id">
              <xsl:text/>[<a href="#{$up-id}">Up</a>]<xsl:text/>
            </xsl:if>
            <xsl:if test="$top-id">
              <xsl:text/> [<a href="#{$top-id}">Top</a>]<xsl:text/>
            </xsl:if>
          </td>
        </tr>
      </table>
    </xsl:if>
  </xsl:template>

  <xsl:variable name="page-title">
    <xsl:value-of select="$TITLE"/>
    <xsl:text>: </xsl:text>
    <xsl:value-of select="testsuite/@profile"/>
  </xsl:variable>

  <xsl:template match="/">
  <xsl:if test="$DEBUG">
    <xsl:message>testsuite-files: '<xsl:value-of select="$testsuite-files"/>'</xsl:message>
    <xsl:message>testsuite-nodes: '<xsl:value-of select="$testsuite-nodes"/>'</xsl:message>
  </xsl:if>
  
    <xsl:apply-templates select="." mode="testresults"/>
  </xsl:template>

  <xsl:template match="/" mode="testresults">
    <html>
      <head>
        <title>
          <xsl:value-of select="$page-title"/>
        </title>
        <link rel="stylesheet" type="text/css" href="style.css"/>
      </head>
      <body>
        <h1>
          <xsl:value-of select="$page-title"/>
        </h1>
        <xsl:if test="$date">
          <p>Report created: <xsl:value-of select="$date"/></p>
        </xsl:if>
        <xsl:apply-templates/>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="testsuite">
    <xsl:variable name="testsuite-id"
      select="translate(@profile, ' ', '-')"/>
    <xsl:variable name="all-testresults"
      select=".//testresult"/>
    <xsl:variable name="full-results-count"
      select="count($all-testresults[@agreement='full' and . != $not-verified-string])"/>
    <xsl:variable name="issues-results-count"
      select="count($all-testresults[@agreement='issues' and . != $not-verified-string])"/>
    <xsl:variable name="not-verified-results-count"
      select="count($all-testresults[.=$not-verified-string])"/>
    <xsl:variable name="total-results-count" select="count($all-testresults)"/>
    <xsl:variable name="full-results-percent"
      select="format-number($full-results-count div $total-results-count, '##0.#%')"/>
    <xsl:variable name="issues-results-percent"
       select="format-number($issues-results-count div $total-results-count, '##0.#%')"/>
    <xsl:variable name="not-verified-results-percent"
       select="format-number(($total-results-count - $full-results-count - $issues-results-count) div $total-results-count, '##0.#%')"/>

    <xsl:message>Full:         <xsl:value-of select="$full-results-count"/> (<xsl:value-of select="$full-results-percent"/>)</xsl:message>
    <xsl:message>Issues:       <xsl:value-of select="$issues-results-count"/> (<xsl:value-of select="$issues-results-percent"/>)</xsl:message>
    <xsl:message>Not verified: <xsl:value-of select="$not-verified-results-count"/> (<xsl:value-of select="$not-verified-results-percent"/>)</xsl:message>
    <xsl:message>Total:        <xsl:value-of select="$total-results-count"/></xsl:message>

     <table width="100%" class="coloured5">
       <tr>
         <td>
          <h2>
            <a name="{$testsuite-id}">
              <xsl:value-of select="@profile"/>
            </a>
          </h2>
        </td>
      </tr>
    </table>
    <table width="95%" class="summary">
      <tr>
        <td class="full">Full</td>
        <td class="differ">Issues</td>
        <xsl:if test="$not-verified-results-count">
          <td class="not-yet-verified">Not yet verified</td>
        </xsl:if>
        <td class="coloured2" style="border-style: none">Total</td>
      </tr>
      <tr class="coloured">
        <td><xsl:value-of select="$full-results-count"/></td>
        <td>
          <xsl:value-of select="$issues-results-count"/>
        </td>
        <xsl:if test="$not-verified-results-count">
          <td>
            <xsl:value-of select="$not-verified-results-count"/>
          </td>
        </xsl:if>
        <td>
          <xsl:value-of select="count($all-testresults)"/>
        </td>
      </tr>
      <tr class="coloured">
        <td>
          <xsl:value-of select="$full-results-percent"/>
        </td>
        <td>
          <xsl:value-of select="$issues-results-percent"/>
        </td>
        <xsl:if test="$not-verified-results-count">
          <td>
            <xsl:value-of select="$not-verified-results-percent"/>
          </td>
        </xsl:if>
        <td>100%</td>
      </tr>
    </table>
    <xsl:if test="$REFERENCE and $OUTPUT_INDIVIDUAL = 'yes'">
      <table style="margin-top: 12pt; margin-bottom: 12pt">
        <xsl:variable name="tests-with-differences" select="count($testsuccess-node/directory/pdf/diff[*[@size != 0]])"/>
        <xsl:message><xsl:value-of select="$tests-with-differences"/> tests with differences</xsl:message>
        <tr class="coloured2">
          <td><xsl:value-of select="$tests-with-differences"/> tests with differences</td>
        </tr>
        <xsl:if test="$tests-with-differences > 0">
          <tr class="coloured">
            <td>
              <xsl:for-each select="$testsuccess-node/directory/pdf[diff/*[@size != 0]]">
                <xsl:sort/>
                <a href="{ancestor::directory/@name}/{substring-before(@name, '.pdf')}.html" target="_blank">
                  <xsl:value-of select="substring-before(@name, '.pdf')"/>
                </a>
                <xsl:text> </xsl:text>
              </xsl:for-each>
            </td>
          </tr>
        </xsl:if>
      </table>
    </xsl:if>
    <table style="border-collapse: collapse">
      <xsl:apply-templates>
        <xsl:with-param name="testsuite-id" select="$testsuite-id"/>
      </xsl:apply-templates>
    </table>
  </xsl:template>

  <xsl:template match="testcases">
    <xsl:param name="my-testcases-id"
      select="translate(normalize-space(@profile), ' ', '-')"/>
    <xsl:param name="testsuite-id"/>
    <xsl:param name="top-testcases-id"
      select="$my-testcases-id"/>
    <xsl:param name="results-top-base" select="@base"/>

    <tr>
      <td colspan="3" class="coloured4 left">
        <h2 class="testcases">
          <a name="{$my-testcases-id}">
            <xsl:value-of select="@profile"/>
          </a>
        </h2>
      </td>
      <td class="coloured4 right">
        <xsl:call-template name="nav-table">
          <xsl:with-param name="top-id" select="$testsuite-id"/>
        </xsl:call-template>
      </td>
    </tr>

    <xsl:apply-templates>
      <xsl:with-param name="testsuite-id" select="$testsuite-id"/>
      <xsl:with-param name="top-testcases-id" select="$top-testcases-id"/>
      <xsl:with-param name="results-top-base" select="$results-top-base"/>
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="testcases/testcases">
    <xsl:param name="my-testcases-id"
      select="translate(normalize-space(@profile), ' ', '-')"/>
    <xsl:param name="testsuite-id"/>
    <xsl:param name="top-testcases-id"
      select="$my-testcases-id"/>
    <xsl:param name="results-top-base" select="@base"/>

    <tr class="coloured3">
      <td colspan="3" class="testcases2  left">
        <h3>
          <a name="{$my-testcases-id}">
            <xsl:value-of select="@profile"/>
          </a>
        </h3>
      </td>
      <td class="testcases2 right">
        <xsl:call-template name="nav-table">
          <xsl:with-param name="top-id" select="$testsuite-id"/>
        </xsl:call-template>
      </td>
    </tr>

    <xsl:apply-templates>
      <xsl:with-param name="testsuite-id" select="$testsuite-id"/>
      <xsl:with-param name="top-testcases-id" select="$top-testcases-id"/>
      <xsl:with-param name="results-top-base" select="$results-top-base"/>
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="testcases/testcases/testcases">
    <xsl:param name="my-testcases-id"
      select="translate(normalize-space(@profile), ' ', '-')"/>
    <xsl:param name="testsuite-id"/>
    <xsl:param name="top-testcases-id"
      select="$my-testcases-id"/>
    <xsl:param name="results-top-base" select="@base"/>

    <tr>
      <xsl:attribute name="class">
        <xsl:text>coloured2</xsl:text>
        <xsl:if test="not(*)">
          <xsl:text> last left</xsl:text>
        </xsl:if>
      </xsl:attribute>
      <td colspan="3" class="testcases3 left">
        <h4>
          <a name="{$my-testcases-id}">
            <xsl:value-of select="@profile"/>
          </a>
        </h4>
      </td>
      <td class="testcases3 right">
        <xsl:call-template name="nav-table">
          <xsl:with-param name="top-id" select="$testsuite-id"/>
        </xsl:call-template>
      </td>
    </tr>

    <xsl:apply-templates>
      <xsl:with-param name="testsuite-id" select="$testsuite-id"/>
      <xsl:with-param name="top-testcases-id" select="$top-testcases-id"/>
      <xsl:with-param name="results-top-base" select="$results-top-base"/>
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="testcases/testcases/testcases/testcases">
    <xsl:param name="my-testcases-id"
      select="translate(normalize-space(@profile), ' ', '-')"/>
    <xsl:param name="testsuite-id"/>
    <xsl:param name="top-testcases-id"
      select="$my-testcases-id"/>
    <xsl:param name="results-top-base" select="@base"/>

    <tr class="coloured">
      <td colspan="3" class="testcases4 left">
        <h4>
          <a name="{$my-testcases-id}">
            <xsl:value-of select="@profile"/>
          </a>
        </h4>
      </td>
      <td class="testcases4 right">
        <xsl:call-template name="nav-table">
          <xsl:with-param name="top-id" select="$testsuite-id"/>
        </xsl:call-template>
      </td>
    </tr>

    <xsl:apply-templates>
      <xsl:with-param name="testsuite-id" select="$testsuite-id"/>
      <xsl:with-param name="top-testcases-id" select="$top-testcases-id"/>
      <xsl:with-param name="results-top-base" select="$results-top-base"/>
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="testresult">
    <xsl:param name="testsuite-id"/>
    <xsl:param name="top-testcases-id"/>
    <xsl:param name="results-top-base" select="(ancestor::*/@base)[1]"/>

    <xsl:variable name="testresult-id"
      select="concat('result-',
                     $top-testcases-id,
                     '-',
                     translate(normalize-space(@id), ' ', '-'))"/>
    <xsl:variable name="id" select="@id"/>
    <xsl:variable name="results" select="@results"/>
    <xsl:variable name="pdf-name">
      <xsl:for-each select="$testsuccess-node">
        <xsl:value-of
          select="key('PDF', $results)[ancestor::*/@name =
                                         $results/ancestor::*/@base]/@name"/>
      </xsl:for-each>
    </xsl:variable>
    <xsl:variable name="pdf-size">
      <xsl:for-each select="$testsuccess-node">
        <xsl:value-of
          select="key('PDF', $results)[ancestor::*/@name =
                                         $results/ancestor::*/@base]/@size"/>
      </xsl:for-each>
    </xsl:variable>
    <tr>
      <xsl:if test="count(following-sibling::*) mod 2 = 0">
        <xsl:attribute name="class">coloured</xsl:attribute>
      </xsl:if>
      <td>
        <xsl:if test="not(following-sibling::testresult)">
          <xsl:attribute name="class">last left</xsl:attribute>
        </xsl:if>
        <a name="{$testresult-id}" class="test-id">
          <xsl:value-of select="$id"/>
        </a>
      </td>
      <td>
        <xsl:call-template name="attribute-table"/>
      </td>
      <td>
        <!-- Process any text describing the test results. -->
        <xsl:apply-templates/>
      </td>
      <td>
        <xsl:if test="not(following-sibling::testresult)">
          <xsl:attribute name="class">last right</xsl:attribute>
        </xsl:if>
        <xsl:if test="$pdf-name != '' and $pdf-size != 0">
          <a>
            <xsl:attribute name="href">
              <xsl:if test="ancestor::testcases/@base">
                <xsl:value-of select="(ancestor::testcases/@base)[1]"/>
                <xsl:text>/</xsl:text>
              </xsl:if>
              <xsl:value-of select="@results"/>
            </xsl:attribute>
            <xsl:text>PDF</xsl:text>
          </a>
        </xsl:if>
        <xsl:text> </xsl:text>
        <xsl:for-each select="$testsuccess-node">
          <xsl:variable name="pdf"
            select="key('PDF', $results)[ancestor::*/@name =
            $results/ancestor::*/@base]"/>
          <xsl:variable name="page-count">
            <xsl:choose>
              <xsl:when test="not($pdf) or $pdf/@size = 0">
                <xsl:text>No output</xsl:text>
              </xsl:when>
              <xsl:otherwise>
                <!-- Number of pages in the PDF. -->
                <xsl:value-of select="$pdf/pwd/@count"/>
              </xsl:otherwise>
            </xsl:choose>
          </xsl:variable>
          <xsl:choose>
            <xsl:when test="$OUTPUT_INDIVIDUAL = 'yes'">
              <a href="{($results/ancestor::*/@base)}/{$id}.html" target="_blank">
                <!-- Are there also diff files? -->
                <xsl:if test="($pdf/diff/@count != 0) and
                              ($pdf/diff/*[@size != 0])">
                  <xsl:attribute name="style">
                    <xsl:text>font-weight: bold; color: white; background-color: red</xsl:text>
                  </xsl:attribute>
                </xsl:if>
                <xsl:value-of select="$page-count"/>
              </a>
              <exsl:document href="./{$results-top-base}/{$id}.html" encoding="UTF-8">
                <xsl:call-template name="results-doc">
                  <xsl:with-param name="pdf" select="$pdf"/>
                  <xsl:with-param name="results" select="$results/.."/>
                  <xsl:with-param name="results-top-base" select="$results-top-base"/>
                  <xsl:with-param name="id" select="$id"/>
                </xsl:call-template>
              </exsl:document>
            </xsl:when>
            <xsl:otherwise>
              <xsl:value-of select="$page-count"/>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:for-each>
      </td>
    </tr>
  </xsl:template>

  <xsl:template name="add-links">
    <xsl:param name="string" select="."/>
    <xsl:choose>
      <xsl:when test="not(contains($string, '#'))">
        <xsl:value-of select="$string"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="substring-before($string, '#')"/>
        <xsl:call-template name="do-link">
          <xsl:with-param name="string"
            select="substring-after($string, '#')"/>
        </xsl:call-template>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="do-link">
    <xsl:param name="string"/>
    <xsl:param name="ticket-number" select="''"/>
    <xsl:choose>
      <xsl:when test="($string = '') and ($ticket-number = '')">
        <xsl:text>#</xsl:text>
      </xsl:when>
      <xsl:when test="($string = '') and ($ticket-number != '')">
        <a href="{$TRAC}{$ticket-number}">
          <xsl:text>#</xsl:text>
          <xsl:value-of select="$ticket-number"/>
        </a>
      </xsl:when>
      <xsl:otherwise>
        <xsl:choose>
          <xsl:when test="translate(substring($string, 1, 1),
                                    '0123456789',
                                    '') = ''">
            <xsl:call-template name="do-link">
              <xsl:with-param name="string"
                select="substring($string, 2)"/>
              <xsl:with-param name="ticket-number"
                select="concat($ticket-number,
                               substring($string, 1, 1))"/>
            </xsl:call-template>
          </xsl:when>
          <xsl:otherwise>
            <a href="{$TRAC}{$ticket-number}">
              <xsl:text>#</xsl:text>
              <xsl:value-of select="$ticket-number"/>
            </a>
            <xsl:call-template name="add-links">
              <xsl:with-param name="string" select="$string"/>
            </xsl:call-template>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="attribute-table">
      <table border="1" width="100%">
      <tr>
        <td align="center" width="33%">
          <xsl:attribute name="class">
            <xsl:choose>
              <xsl:when test="@agreement = 'issues' and . = $not-verified-string">
                <xsl:text/>other</xsl:when>
              <xsl:when test="@agreement = 'full'">
                <xsl:text/>full</xsl:when>
              <xsl:otherwise>differ</xsl:otherwise>
            </xsl:choose>
          </xsl:attribute>
          <xsl:choose>
            <xsl:when test="@agreement = 'issues' and . = $not-verified-string">
              <xsl:text/>&#160;</xsl:when>
            <xsl:when test="@agreement = 'full'">
              <xsl:text>Full</xsl:text>
            </xsl:when>
            <xsl:otherwise>Issues</xsl:otherwise>
          </xsl:choose>
        </td>
        <td align="center" width="34%">
          <xsl:attribute name="class">
            <xsl:choose>
              <xsl:when test="@specproblem = 'yes'">
                <xsl:text/>spec</xsl:when>
              <xsl:otherwise>other</xsl:otherwise>
            </xsl:choose>
          </xsl:attribute>
          <xsl:choose>
            <xsl:when test="@specproblem = 'yes'">
              <xsl:text/>Spec</xsl:when>
            <xsl:otherwise>&#160;</xsl:otherwise>
          </xsl:choose>
        </td>
        <td align="center" width="33%">
          <xsl:attribute name="class">
            <xsl:choose>
              <xsl:when test="@testproblem = 'yes'">
                <xsl:text>test</xsl:text>
	      </xsl:when>
              <xsl:otherwise>other</xsl:otherwise>
            </xsl:choose>
          </xsl:attribute>
          <xsl:choose>
            <xsl:when test="@testproblem = 'yes'">
              <xsl:text>Test</xsl:text>
	    </xsl:when>
            <xsl:otherwise>&#160;</xsl:otherwise>
          </xsl:choose>
        </td>
      </tr>
    </table>
  </xsl:template>


  <xsl:template name="munged-a">
    <xsl:param name="href"/>
    <xsl:param name="content"/>
    <xsl:param name="test-file-dirname"/>

    <xsl:variable name="href-dirname">
      <xsl:call-template name="dirname">
        <xsl:with-param name="string" select="$href"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="full-href">
      <xsl:call-template name="merge-dirnames">
        <xsl:with-param name="dirname1" select="$test-file-dirname"/>
        <xsl:with-param name="dirname2" select="$href-dirname"/>
			</xsl:call-template>
      <xsl:call-template name="basename">
        <xsl:with-param name="string" select="$href"/>
      </xsl:call-template>
    </xsl:variable>

    <!-- Heuristic to work out which href value to use. -->
    <xsl:variable name="use-href">
      <xsl:choose>
        <xsl:when test="starts-with($full-href, '/usr/local/src/xslfo')">
          <xsl:text>/xmlroff</xsl:text>
          <xsl:value-of select="substring-after($full-href, 'usr/local/src/xslfo')"/>
        </xsl:when>
        <xsl:when test="starts-with($full-href, '/usr/local/src/TestSuite')">
          <xsl:text>/xmlroff</xsl:text>
          <xsl:value-of select="substring-after($full-href, 'usr/local/src')"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$full-href"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:if test="$DEBUG">
      <xsl:message>munged-a:: full-href: '<xsl:value-of select="$full-href"/>; test-file-dirname: '<xsl:value-of select="$test-file-dirname"/>'</xsl:message>
      <xsl:message>munged-a:: use-href: '<xsl:value-of select="$use-href"/>; content: '<xsl:value-of select="$content"/>'</xsl:message>
    </xsl:if>
    
    <a href="{$use-href}">
      <xsl:copy-of select="$content"/>
    </a>
  </xsl:template>

  <xsl:template match="text()">
    <!-- Makes ticket references in text into links to Trac
         tickets unless the feature is disabled. -->
    <xsl:choose>
      <xsl:when test="$TRAC != 'no'">
        <xsl:call-template name="add-links"/>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="."/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
</xsl:stylesheet>
